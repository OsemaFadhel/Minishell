/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:25:43 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/10 22:26:01 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_closed_dquotes(char *cmd, int i)
{
	int	quotes;

	quotes = 0;
	while (cmd[i] && quotes != 2)
	{
		if (cmd[i] == '\"')
			quotes++;
		i++;
	}
	if (quotes != 2)
		return (1);
	return (0);
}

int	check_closed_quotes(char *cmd, int i)
{
	int	quotes;

	quotes = 0;
	while (cmd[i] && quotes != 2)
	{
		if (cmd[i] == '\'')
			quotes++;
		i++;
	}
	if (quotes != 2)
		return (1);
	return (0);
}

void	add_pipe_char(char *cmd, t_mini *mini, t_lexer *lexer)
{
	mini->toks[lexer->j][0] = cmd[lexer->i];
	mini->toks[lexer->j][1] = '\0';
	lexer->i++;
	lexer->j++;
}

void	add_single_char(char *cmd, t_mini *mini, t_lexer *lexer)
{
	mini->toks[lexer->j][0] = cmd[lexer->i];
	mini->toks[lexer->j][1] = '\0';
	lexer->i++;
	lexer->j++;
}

void	add_redirect(char *cmd, t_mini *mini, t_lexer *lexer)
{
	mini->toks[lexer->j][0] = cmd[lexer->i];
	mini->toks[lexer->j][1] = cmd[lexer->i + 1];
	mini->toks[lexer->j][2] = '\0';
	lexer->i += 2;
	lexer->j++;
}
