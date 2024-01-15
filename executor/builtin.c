/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/16 00:55:45 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_setenv(t_mini *mini, char *name, char *value)
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
		new_env = ft_calloc(sizeof(char *), (i + 1));
	else
		new_env = ft_calloc(sizeof(char *), (i + 2));
	i = 0;
	while (mini->env[i])
	{
		if (i == pos)
		{
			tmp = ft_strjoin(name, value);
			new_env[i] = ft_strdup(tmp);
			free(tmp);
			i++;
		}
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
	}
	if (pos == -1)
	{
		tmp = ft_strjoin(name, value);
		new_env[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	new_env[i] = NULL;
	ft_free_array(mini->env);
	mini->env = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (new_env[i])
	{
		mini->env[i] = ft_strdup(new_env[i]);
		i++;
	}
	ft_free_array(new_env);
	return (0);
}

void	update_pwd(t_mini *mini)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_setenv(mini, "PWD=", buf);
	free(buf);
}

int	ft_cd(t_mini *mini, t_cmds *current_cmd)
{
	char	*path;
	char	*oldpwd;

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
		oldpwd = get_env_var("PWD=", mini->env);
		g_exit_status = 0;
		update_pwd(mini);
		ft_setenv(mini, "OLDPWD=", oldpwd);
		free(oldpwd);
	}
	return (0);
}

int	ft_export(t_mini *mini, t_cmds *current_cmd)
{
	return (0);
}

int	ft_unset(t_mini *mini, t_cmds *current_cmd)
{
	return (0);
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
	else if (ft_strncmp(current_cmd->cmd, "export", 7) == 0)
		ft_export(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "unset", 6) == 0)
		ft_unset(mini, current_cmd);
	else
		return (0);
	return (1);
}
