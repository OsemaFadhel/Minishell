/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:36:53 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 22:49:22 by ofadhel          ###   ########.fr       */
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

int	sub_count_words(char *cmd, int i, t_lexer *lexer)
{
	if (cmd[i] == '\"')
	{
		i = count_words_2(cmd, i, lexer->words);
		lexer->words++;
	}
	else if (cmd[i] == '\'')
	{
		i = count_words_3(cmd, i, lexer->words);
		lexer->words++;
	}
	else if ((cmd[i] == '>' && cmd[i + 1] == '>') | (cmd[i] == '<' && cmd[i + 1] == '<'))
	{
		lexer->words += 2;
		i++;
	}
	else if (cmd[i] == '>' | cmd[i] == '<')
	{
		lexer->words++;
		i++;
	}
	else
		return (-1);
	return (i);
}

int	count_words_lex(char *cmd, t_lexer *lexer)
{
	int	i;

	i = 0;
	lexer->words = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		else if (sub_count_words(cmd, i, lexer) != -1)
			i = sub_count_words(cmd, i, lexer);
		else
		{
			while (cmd[i] != ' ' && cmd[i] != '\0' && (check_closed_dquotes(cmd, i) == 1 || check_closed_quotes(cmd, i) == 1))
			{
				if ((cmd[i] == '>' && cmd[i + 1] == '>') | (cmd[i] == '<' && cmd[i + 1] == '<'))
					break;
				if (cmd[i] == '>' | cmd[i] == '<')
					break;
				i++;
			}
			lexer->words++;
		}
	}
	return (lexer->words);
}
