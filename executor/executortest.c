/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/19 14:06:16 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//create first other process to execute the command
//if the command is not built-in, execute it with execve
//execve will close the process

void	executor(t_mini	*mini)
{
	int	i;
	char *bin;
	char *path;

	i = 0;
	bin = "/bin/";
	if (!is_builtin(mini, i))
		return ;
	else
	{
		//check if there is a path in the command
		//if there is, execute it with execve
		//else, execute it with /bin/ + command
		if(strchr(mini->toks[0], '/'))
			path = mini->toks[0];
		else
		{
			//malloc the path and copy the bin + command into it (strcat
			path = malloc(sizeof(char) * (ft_strlen(bin) + ft_strlen(mini->toks[0]) + 1));
			strcpy(path, bin);
			strcat(path, mini->toks[0]);
		}
		if (execve(path, mini->toks, mini->env)) //execve will close the process.
			perror("niggawhat$");
	}
}
