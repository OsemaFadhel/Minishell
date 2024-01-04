/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/04 16:27:30 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//create first other process to execute the command
//if the command is not built-in, execute it with execve
//execve will close the process

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
		execve(path, cmds->args, NULL); //execve will close the process.
		//perror("BASH$");
	}
}
