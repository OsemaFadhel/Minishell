/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:32:21 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/20 16:06:23 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_mini	*mini)
{
	int	i;
	char *bin;
	char *path;

	bin = "/bin/";
	if (strcmp(mini->cmds[0], "exit") == 0)
			exit(0);
	else if (strcmp(mini->cmds[0], "env") == 0)
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
	else //execute bash cmds after checking if the command is not built-in->
	{
		path = malloc(sizeof(char) * (strlen(bin) + strlen(mini->cmds[0]) + 1));
		strcpy(path, bin);
		strcat(path, mini->cmds[0]);
		if (execve(path, mini->cmds, mini->envp)) //execve will close the process.
			perror("minishell$");
	}
}
