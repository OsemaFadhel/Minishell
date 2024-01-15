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

static void handle_exit_args(t_mini *mini, t_cmds *current_cmd)
{
    // Check if there is an argument for exit status
    if (current_cmd->args[1] != NULL)
    {
        char *endptr;
        long exit_status = strtol(current_cmd->args[1], &endptr, 10);

        if (*endptr != '\0' || errno == ERANGE)
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(current_cmd->args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            g_exit_status = 2; // Default exit status
            return;
        }

        g_exit_status = (int)exit_status;
    }
}

int ft_exit(t_mini *mini, t_cmds *current_cmd)
{
    // Ignore unused parameter warning
    (void)current_cmd;

    // Handle exit arguments
    handle_exit_args(mini, current_cmd);

    // Free allocated memory
    free_cmds(&*mini);

    // Perform cleanup or additional actions as needed
    // ...

    // Exit with the specified status
    exit(g_exit_status);

    // This return statement is not reachable but added for completeness
    return (g_exit_status);
}

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