/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/15 20:53:12 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//#include <stdbool.h>

int	ft_echo(t_mini *mini __attribute((unused)), t_cmds *current_cmd) //completed
{
	int		i;
	int		newline;

	newline = 0;
	i = 1;
	while (current_cmd->args[i] && !ft_strncmp(current_cmd->args[i], "-n", 3))
		i++;
	if (i == 1)
		newline = 1;
	while (current_cmd->args[i])
	{
		ft_putstr_fd(current_cmd->args[i], 1);
		if (current_cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
	return (0);
}

int	ft_pwd(t_mini *mini, t_cmds *current_cmd) //completed
{
	char	*path;

	(void)current_cmd;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	g_exit_status = 0;
	return (0);
}

int	ft_env(t_mini *mini, t_cmds *current_cmd) //completed
{
	int	i;

	i = 0;
	(void)current_cmd;
	while (mini->env[i])
	{
		ft_putstr_fd(mini->env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	g_exit_status = 0;
	return (0);
}

int	ft_setenv(t_mini *mini, char *name, char *value) //completed
{
	int		i;
	char	**new_env;
	char	*tmp;
	int		pos;

	pos = -1;
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], name, ft_strlen(name)) == 0)
			pos = i;
		i++;
	}
	if (pos != -1)
		new_env = ft_calloc(sizeof(char *), i + 2);
	else
		new_env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (mini->env[i])
	{
		if (i == pos)
		{
			tmp = ft_strjoin(name, "=");
			tmp = ft_strjoin(tmp, value);
			new_env[i] = ft_strdup(tmp);
			free(tmp);
			i++;
		}
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
	}
	if (pos == -1)
	{
		tmp = ft_strjoin(name, "=");
		tmp = ft_strjoin(tmp, value);
		new_env[i] = ft_strdup(tmp);
		free(tmp);
	}
	new_env[i + 1] = NULL;
	ft_free_array(mini->env);
	mini->env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (new_env[i])
	{
		mini->env[i] = ft_strdup(new_env[i]);
		i++;
	}
	mini->env[i] = NULL;
	ft_free_array(new_env);
	return (0);
}

void	update_pwd(t_mini *mini)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_setenv(mini, "PWD", buf);
}

int	ft_cd(t_mini *mini, t_cmds *current_cmd)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (current_cmd->args[1] == NULL)
		path = getenv("HOME");
	else if (ft_strncmp(current_cmd->args[1], "-", 2) == 0)
	{
		path = get_env_var("OLDPWD=", mini->env);
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			g_exit_status = 1;
			return (0);
		}
	}
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
		perror("cd");
		g_exit_status = 1;
	}
	else
	{
		g_exit_status = 0;
		update_pwd(mini);
		ft_setenv(mini, "OLDPWD", oldpwd);
	}
	return (0);
}

static int str_to_int(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (ft_isdigit(str[i]))
    {
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
            return -1;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
		return -1;
    return result * sign;
}

int	handle_exit_args(t_mini *mini, t_cmds *current_cmd)
{
	char *endptr;
	int exit_status;


	if (current_cmd->args[1] != NULL)
	{
		exit_status = str_to_int(current_cmd->args[1]);
		if (exit_status == -1)
		{
			printf("exit: %s: numeric argument required\n",
				current_cmd->args[1]);
			g_exit_status = 255;
			return 0;
		}
		if (current_cmd->args[2] != NULL)
		{
			ft_putstr_fd("BASH: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return 1;
		}
		g_exit_status = exit_status;
	}
	return 0;
}

int	ft_exit(t_mini *mini, t_cmds *current_cmd)
{
	(void)current_cmd;
	if (handle_exit_args(mini, current_cmd) == 1)
		return (0);
	free_cmds(&*mini);
	ft_free_array(mini->env);
	exit(g_exit_status);
}

int	is_builtin(t_mini *mini, t_cmds *current_cmd)
{
	if (ft_strncmp(current_cmd->cmd, "echo", 5) == 0)
		ft_echo(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "cd", 3) == 0)
		ft_cd(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "exit", 5) == 0)
		ft_exit(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "pwd", 4) == 0)
		ft_pwd(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "env", 4) == 0)
		ft_env(mini, current_cmd);
	else
		return (0);
	return (1);
}
