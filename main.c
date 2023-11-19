/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/19 22:47:29 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**line;
	char  	*input;
	char 	*env;
	t_mini	mini;
	int		i;

	env = ft_strdup(envp[0]);
	while (1)
	{
		input = readline("minishell$ ");
		line = ft_split(input, ' ');
		if (!line)
			break ;
		add_history(input);
		//lexer(line, &mini);
		if (strcmp(line[0], "exit") == 0)
			break ;
		else if (strcmp(line[0], "env") == 0)
		{
			i = 0;
			while (envp && envp[0] && envp[i])
			{
				env = ft_strdup(envp[i]);
				printf("%s\n", env);
				i++;
			}
			printf("\n");
		}
		else
		{
			char *bin = "/bin/";
			char *path = malloc(sizeof(char) * (strlen(bin) + strlen(line[0]) + 1));

			strcpy(path, bin);
			strcat(path, line[0]);
			if (execve(path, line, envp)) //execve will close the process.
				perror("minishell$");
		}
		free(input);
		i = 0;
		while (line[i])
		{
			free(line[i]);
			i++;
		}
		free(line);
	}
	return (0);
}
