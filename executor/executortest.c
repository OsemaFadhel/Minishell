/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/04 19:57:07 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//create first other process to execute the command
//if the command is not built-in, execute it with execve
//execve will close the process

int		search_env(char **env, char *str)
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

void	executor(t_mini	*mini, t_cmds *cmds)
{
	int	i;
	char *bin;
	char *path;

	i = 0;
	bin = "/bin/";
	//if (!is_builtin(mini, cmds, i))
	//	return ;
	if (1)
	{
		//check if there is a path in the command
		//if there is, execute it with execve
		//else, execute it with /bin/ + command
		if (search_env(mini->env, "PATH") == -1)
		{
			printf("Error: No such file or directory\n");
			return ;
		}
		if(ft_strchr(cmds->cmd, '/'))
			path = cmds->cmd;
		else
		{
			//malloc the path and copy the bin + command into it (strcat
			path = malloc(sizeof(char) * (ft_strlen(bin) + ft_strlen(cmds->cmd) + 1));
			strcpy(path, bin);
			strcat(path, cmds->cmd);
		}
		i = 0;
		execve(path, cmds->args, mini->env); //execve will close the process.
		//perror("BASH$");
	}
}
