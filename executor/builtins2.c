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
    return (0);
}

char *env_get_value(const char *name)
{
    int i;

    if (name == NULL)
        return (NULL);

    i = 0;
    while (g_env[i] != NULL)
    {
        if (ft_strncmp(g_env[i], name, ft_strlen(name)) == 0 && g_env[i][ft_strlen(name)] == '=')
            return (ft_strdup(g_env[i] + ft_strlen(name) + 1));
        i++;
    }
    return (NULL);
}

static int update_pwd(void)
{
    char buf[PATH_MAX];

    if (env_get_value("PWD"))
    {
        if (env_set_env("OLDPWD", env_get_value("PWD")) == ERROR)
            return (ERROR);
    }
    else
        env_unset_var("OLDPWD");

    if (getcwd(buf, sizeof(buf)) == NULL)
    {
        print_error_errno(SHELL_NAME, "cd", NULL);
        return (ERROR);
    }

    if (env_set_env("PWD", buf) == ERROR)
        return (ERROR);

    return (0);
}

int ft_cd(t_mini *mini, t_cmds *current_cmd)
{
    char *path;

    if (current_cmd->args[1] == NULL)
        path = env_get_value("HOME");
    else if (ft_strncmp(current_cmd->args[1], "-", 2) == 0)
        path = env_get_value("OLDPWD");
    else
        path = current_cmd->args[1];

    if (!path)
    {
        ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
        g_exit_status = 1;
        return (0);
    }

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
    }

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
    return (0);
}

int fd_env(t_mini *mini, t_cmds *current_cmd)
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

int fd_exit(t_mini *mini, t_cmds *current_cmd)
{
    // Ignore unused parameter warning
    (void)current_cmd;

    // Handle exit arguments
    handle_exit_args(mini, current_cmd);

    // Free allocated memory
    free_all(mini);

    // Perform cleanup or additional actions as needed
    // ...

    // Exit with the specified status
    exit(g_exit_status);

    // This return statement is not reachable but added for completeness
    return (g_exit_status);
}

int fd_export(t_mini *mini, t_cmds *current_cmd)
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