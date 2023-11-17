/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/17 18:58:14 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*line;
	t_mini	mini;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (strcmp(line, "exit") == 0)
			break ;
		//lexer(line, &mini);
		free(line);
	}
	return (0);
}
