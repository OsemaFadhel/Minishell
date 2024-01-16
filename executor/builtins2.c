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
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(current_cmd->args[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            g_exit_status = 2; // Default exit status
            return;
        }

        // Correctly handle exit status overflow
        g_exit_status = (exit_status % 256 + 256) % 256;
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
    int i = 0;

    if (!str || !str[0])
        return 0;

    while (str[i])
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return 0;
        i++;
    }

    return 1;
}

// Helper function to remove an environment variable from mini->env
static void remove_env_var(t_mini *mini, const char *var)
{
    int i = 0;

    while (mini->env[i])
    {
        if (ft_strncmp(mini->env[i], var, ft_strlen(var)) == 0 && mini->env[i][ft_strlen(var)] == '=')
        {
            // Remove the environment variable by shifting subsequent elements
            free(mini->env[i]);
            while (mini->env[i])
            {
                mini->env[i] = mini->env[i + 1];
                i++;
            }
            break;
        }
        i++;
    }
}

int ft_unset(t_mini *mini, t_cmds *current_cmd)
{
    int i = 1;

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
            remove_env_var(mini, current_cmd->args[i]);
        }

        i++;
    }

    return 0;
}

void env_set_env(t_mini *mini, const char *name, const char *value)
{
    char **env = mini->env;

    // Iterate through the environment variables
    for (int i = 0; env[i] != NULL; i++)
    {
        // Check if the variable matches the given name
        if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=')
        {
            // Update the existing variable
            free(env[i]);
            char *new_var = ft_strjoin(name, "=");
            env[i] = ft_strjoin(new_var, value);
            free(new_var);
            return;
        }
    }

    // If the variable doesn't exist, add a new one
    char *new_var = ft_strjoin(name, "=");
    char *new_entry = ft_strjoin(new_var, value);
    free(new_var);

    // Count the number of existing environment variables
    int env_count = 0;
    while (env[env_count] != NULL)
        env_count++;

    // Allocate memory for the new environment
    char **new_env = (char **)malloc((env_count + 2) * sizeof(char *));

    // Copy the existing environment variables
    for (int i = 0; i < env_count; i++)
        new_env[i] = ft_strdup(env[i]);

    // Add the new variable
    new_env[env_count] = ft_strdup(new_entry);
    new_env[env_count + 1] = NULL;

    // Free the old environment and update the global variable
    ft_free_array(env);
    mini->env = new_env;

    free(new_entry);
}

// Function to get the value of an environment variable
char *env_get_value(t_mini *mini, const char *name)
{
    char **env = mini->env;

    // Iterate through the environment variables
    for (int i = 0; env[i] != NULL; i++)
    {
        // Check if the variable matches the given name
        if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=')
        {
            // Return the value of the variable
            return ft_strdup(env[i] + ft_strlen(name) + 1);
        }
    }

    // Return NULL if the variable is not found
    return NULL;
}

void print_vars(char **envp) {
    int i;
    char **tmp;

    i = 0;
    tmp = envp;
    while (tmp[i] != NULL) {
        if (i == 0)
            ft_putstr_fd("declare -x ", 1);

        // Print variable name
        int j = 0;
        while (tmp[i][j] != '\0' && tmp[i][j] != '=')
            ft_putchar_fd(tmp[i][j++], 1);

        if (tmp[i][j] == '=') {
            // Print variable value between double quotes
            ft_putstr_fd("=\"", 1);

            // Skip the '=' character and print the value
            j++;
            while (tmp[i][j] != '\0')
                ft_putchar_fd(tmp[i][j++], 1);

            ft_putstr_fd("\"\n", 1);
        } else {
            // If no '=' is found, just print a newline
            ft_putchar_fd('\n', 1);
        }

        i++;
    }
}


int ft_export(t_mini *mini, t_cmds *current_cmd)
{
    int i = 1;

        if (current_cmd->args[i] == NULL)
    {
        print_vars(mini->env);
        return 0;
    }
    while (current_cmd->args[i])
    {
        if (!is_valid_identifier(current_cmd->args[i]))
        {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(current_cmd->args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            g_exit_status = 1;
        }
        else if (ft_strchr(current_cmd->args[i], '='))
        {
            char *var = ft_substr(current_cmd->args[i], 0, ft_strchr(current_cmd->args[i], '=') - current_cmd->args[i]);
            char *value = ft_strchr(current_cmd->args[i], '=') + 1;
            env_set_env(mini, var, value);
            free(var);
        }
        else
        {
            char *value = env_get_value(mini, current_cmd->args[i]);
            if (value)
                env_set_env(mini, current_cmd->args[i], value);
            else
                env_set_env(mini, current_cmd->args[i], "");
        }

        i++;
    }

    return 0;
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