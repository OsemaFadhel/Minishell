/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/14 22:34:57 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_env(char **env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j] == str[j] && str[j] != '\0')
		{
			if (str[j + 1] == '\0' && env[i][j + 1] == '=')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	check_bin(t_mini *mini, t_cmds *cmds)
{
	struct stat	buf;
	char		**path;
	char		*bin;
	int			i;

	if (search_env(mini->env, "PATH") == -1)
		return (-1);
	path = ft_split(mini->env[search_env(mini->env, "PATH")] + 5, ':');
	i = 0;
	while (path[i++])
	{
		bin = ft_strjoin(path[i], "/");
		bin = ft_strjoin(bin, cmds->cmd);
		if (access(bin, F_OK) == 0)
		{
			ft_free_array(path);
			free(bin);
			return (i);
		}
		free(bin);
	}
	ft_free_array(path);
	return (0);
}

char	*add_path(t_mini *mini, t_cmds *cmds, int i)
{
	char	**path;
	char	*bin;
	char	*tmp;

	path = ft_split(mini->env[search_env(mini->env, "PATH")] + 5, ':');
	bin = ft_strjoin(path[i], "/");
	tmp = bin;
	bin = ft_strjoin(bin, cmds->cmd);
	free(tmp);
	ft_free_array(path);
	return (bin);
}

void	executor(t_mini	*mini, t_cmds *cmds)
{
	int			i;
	struct stat	buf;

	i = 0;
	if (!cmds->cmd)
		exit(0);
	if (1)
	{
		if (ft_strchr(cmds->cmd, '/'))
			;
		else if (check_bin(mini, cmds) > 0)
		{
			i = check_bin(mini, cmds);
			cmds->cmd = add_path(mini, cmds, i);
		}
		if (access(cmds->cmd, F_OK) == 0)
			execve(cmds->cmd, cmds->args, mini->env);
		else
			perror("BASH$ :");
	}
}

int	ft_fork(t_mini *mini, t_cmds *current_cmd, int tmpin, int tmpout)
{
	pid_t	ret;

	/*if (is_builtin(mini, current_cmd) == 1)
		return (0);
	else
	{*/
		ret = fork();
		mini->exec_flag = 1;
		if (ret == 0)
		{
			close(mini->fdin);
			close(tmpin);
			close(tmpout);
			executor(mini, current_cmd);
			exit(127);
		}
	//}
	return (0);
}
