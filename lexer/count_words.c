/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:36:53 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/14 12:53:15 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_words_2(char *cmd, int i, int words)
{
	if (check_closed_dquotes(cmd, i) == 0)
	{
		i++;
		while (cmd[i] != '\"')
			i++;
		i++;
	}
	else
	{
		i++;
	}
	return (i);
}

int	count_words_3(char *cmd, int i, int words)
{
	if (check_closed_quotes(cmd, i) == 0)
	{
		i++;
		while (cmd[i] != '\'')
			i++;
		i++;
	}
	else
	{
		i++;
	}
	return (i);
}

int	count_words(char *cmd)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		else if (cmd[i] == '\"')
		{
			i = count_words_2(cmd, i, words);
			words++;
		}
		else if (cmd[i] == '\'')
		{
			i = count_words_3(cmd, i, words);
			words++;
		}
		else
		{
			while (cmd[i] != ' ' && cmd[i] != '\0' && (check_closed_dquotes(cmd, i) == 1 || check_closed_quotes(cmd, i) == 1))
				i++;
			words++;
		}
	}
	return (words);
}