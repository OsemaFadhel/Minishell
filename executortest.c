/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/21 15:49:51 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_mini	*mini)
{
	int	i;
	char *bin;
	char *path;

	bin = "/bin/";
	if (strcmp(mini->toks[0], "exit") == 0)
			exit(0);
	if (strcmp(mini->toks[0], "env") == 0)
	{
		i = 0;
		printf("test\n");
		while (mini->envp[i])
		{
			printf("%s\n", mini->envp[i]);
			i++;
		}
		printf("\n");
	}
	else //execute bash toks after checking if the command is not built-in->
	{
		path = malloc(sizeof(char) * (strlen(bin) + strlen(mini->toks[0]) + 1));
		strcpy(path, bin);
		strcat(path, mini->toks[0]);
		if (execve(path, mini->toks, mini->envp)) //execve will close the process.
			perror("niggawhat$");
	}
}
