/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:14:52 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/16 17:29:25 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_env_pos(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (i);
}

char **ft_realloc(char **env, int size)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(sizeof(char *), (size + 1));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}

int	ft_setenv(t_mini *mini, char *name, char *value)
{
	int		i;
	char	*tmp;
	int		pos;

	pos = get_env_pos(name, mini->env);
	i = ft_array_len(mini->env);
	if (mini->env[pos])
	{
		free(mini->env[pos]);
		mini->env[pos] = ft_strjoin(name, value);
		mini->env[i] = NULL;
	}
	else
	{
		mini->env = ft_realloc(mini->env, pos + 1);
		mini->env[pos] = ft_strjoin(name, value);
		mini->env[pos + 1] = NULL;
	}
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
		ft_setenv(mini, "OLDPWD=", oldpwd);
		free(oldpwd);
	}
	return (0);
}
