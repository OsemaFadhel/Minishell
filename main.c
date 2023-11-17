/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/17 22:40:00 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char 	*env;
	t_mini	mini;
	int		i;

	env = ft_strdup(envp[0]);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		//lexer(line, &mini);
		if (strcmp(line, "exit") == 0)
			break ;
		if (strcmp(line, "env") == 0)
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
		free(line);
	}
	return (0);
}