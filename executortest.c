/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/24 16:08:14 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else //execute bash toks after checking if the command is not built-in->
	{
		path = malloc(sizeof(char) * (strlen(bin) + strlen(mini->toks[0]) + 1));
		strcpy(path, bin);
		strcat(path, mini->toks[0]);
		if (execve(path, mini->toks, mini->envp)) //execve will close the process.
			perror("niggawhat$");
	}
}
