#include "../include/minishell.h"

int ft_echo(t_mini *mini __attribute((unused)), t_cmds *current_cmd)
{
    int i;
    bool newline;

    newline = false;
    i = 1;
    while (current_cmd->args[i] && !ft_strncmp(current_cmd->args[i], "-n", 3))
        i++;
    if (i == 1)
        newline = true;
    while (current_cmd->args[i])
    {
        ft_putstr_fd(current_cmd->args[i], STDOUT_FILENO);
        if (current_cmd->args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    printf("echo done\n");
    return (0);
}

void update_pwd(void)
{
    char buf[PATH_MAX];

    if (getcwd(buf, sizeof(buf)) == NULL)
    {
        ft_putstr_fd("cd: error getting current working directory\n", STDERR_FILENO);
        g_exit_status = 1;
        return;
    }

    setenv("PWD", buf, 1); // The third argument (1) indicates to replace the variable if it already exists.
}

int ft_cd(t_mini *mini, t_cmds *current_cmd)
{
    char *path;

    if (current_cmd->args[1] == NULL)
        path = getenv("HOME");
    else if (ft_strncmp(current_cmd->args[1], "-", 2) == 0)
        path = getenv("OLDPWD");
    else
        path = current_cmd->args[1];

    if (!path)
    {
        ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
        g_exit_status = 1;
        return (0);
    }

    char *oldpwd = getenv("PWD");

    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putchar_fd('\n', STDERR_FILENO);
        g_exit_status = 1;
    }
    else
    {
        g_exit_status = 0;
        update_pwd();
        if (oldpwd)
            setenv("OLDPWD", oldpwd, 1); // The third argument (1) indicates to replace the variable if it already exists.
    }
    printf("cd done\n");
    return (0);
}

/*
int ft_cd(t_mini *mini, t_cmds *current_cmd)
{
    char *path;

    if (current_cmd->args[1] == NULL)
        path = getenv("HOME");
    else
        path = current_cmd->args[1];
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putchar_fd('\n', 2);
        g_exit_status = 1;
    }
    else
        g_exit_status = 0;
    return (0);
} */

int    ft_pwd(t_mini *mini, t_cmds *current_cmd)
{
    char *path;

    (void)current_cmd;
    path = getcwd(NULL, 0);
    ft_putstr_fd(path, 1);
    ft_putchar_fd('\n', 1);
    free(path);
    printf("pwd done\n");
    return (0);
}

int ft_env(t_mini *mini, t_cmds *current_cmd)
{
    int i;

    i = 0;
    while (mini->env[i])
    {
        ft_putstr_fd(mini->env[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
    (void)current_cmd;
    printf("env done\n");
    return (0);
}

static int str_to_int(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle sign
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
    {
        i++;
    }

    // Convert to integer
    while (isdigit(str[i]))
    {
        // Check for overflow
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
        {
            return -1; // Overflow
        }

        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Check for extra characters
    if (str[i] != '\0')
    {
        return -1; // Extra characters after the numeric argument
    }

    return result * sign;
}

static void handle_exit_args(t_mini *mini, t_cmds *current_cmd)
{
    // Check if there is an argument for exit status
    if (current_cmd->args[1] != NULL)
    {
        int exit_status = str_to_int(current_cmd->args[1]);

        if (exit_status == -1)
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(current_cmd->args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            g_exit_status = 2; // Default exit status
            return;
        }

        g_exit_status = exit_status;
    }
}

int ft_exit(t_mini *mini, t_cmds *current_cmd)
{
    // Ignore unused parameter warning
    (void)current_cmd;

    // Handle exit arguments
    handle_exit_args(mini, current_cmd);

    // Free allocated memory (replace with your actual function)
     free_cmds(&*mini);

    // Perform cleanup or additional actions as needed
    // ...

    // Exit with the specified status
    // Replace the following line with the appropriate cleanup/free function
    exit(g_exit_status);

    // For testing purposes, print the exit status instead of actually exiting
    ft_putstr_fd("Exiting with status: ", 2);
    ft_putnbr_fd(g_exit_status, 2);
    ft_putchar_fd('\n', 2);

    return (g_exit_status);
}

static int is_valid_identifier(const char *str)
{
    int i;

    if (!str || !str[0])
        return 0;

    i = 0;
    while (str[i])
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return 0;
        i++;
    }

    return 1;
}


int ft_unset(t_mini *mini __attribute((unused)), t_cmds *current_cmd)
{
    int i;
    
    i = 1;
    while (current_cmd->args[i])
    {
        if (!is_valid_identifier(current_cmd->args[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(current_cmd->args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            g_exit_status = 1;
        }
        else
        {
            if (unsetenv(current_cmd->args[i]) != 0)
            {
                ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
                ft_putstr_fd(current_cmd->args[i], STDERR_FILENO);
                ft_putstr_fd("': not found\n", STDERR_FILENO);
                g_exit_status = 1;
            }
        }

        i++;
    }

    return (0);
}

// int ft_exit(t_mini *mini, t_cmds *current_cmd)
// {
//     // Ignore unused parameter warning
//     (void)current_cmd;

//     // Handle exit arguments
//     handle_exit_args(mini, current_cmd);

//     // Free allocated memory
//     free_cmds(&*mini);

//     // Perform cleanup or additional actions as needed
//     // ...

//     // Exit with the specified status
//     exit(g_exit_status);

//     // This return statement is not reachable but added for completeness
//     return (g_exit_status);
// }

/*
int ft_export(t_mini *mini, t_cmds *current_cmd)
{
    int i;
    int j;

    i = 1;
    while (current_cmd->args[i])
    {
        j = 0;
        while (current_cmd->args[i][j])
        {
            if (current_cmd->args[i][j] == '=')
            {
                current_cmd->args[i][j] = '\0';
                break;
            }
            j++;
        }
        if (current_cmd->args[i][j] == '=')
            setenv(mini, current_cmd->args[i], current_cmd->args[i] + j + 1);
        else
            setenv(mini, current_cmd->args[i], "");
        i++;
    }
    return (0);
}
*/