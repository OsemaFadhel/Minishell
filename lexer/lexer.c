/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:53 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/13 16:19:19 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	sub_ifs_lexersplit(char *cmd, t_mini *mini, t_lexer *lexer)
{
	while (cmd[lexer->i] == ' ' || cmd[lexer->i] == '\0')
		lexer->i++;
	if (cmd[lexer->i] == '\"')
	{
		lexer->i = add_str_dquot(cmd, mini, lexer, mini->env);
		lexer->j++;
	}
	else if (cmd[lexer->i] == '\'')
	{
		lexer->i = add_str_quot(cmd, mini, lexer);
		lexer->j++;
	}
	else if ((cmd[lexer->i] == '>' && cmd[lexer->i + 1] == '>')
		|| (cmd[lexer->i] == '<' && cmd[lexer->i + 1] == '<'))
		add_redirect(cmd, mini, lexer);
	else if (cmd[lexer->i] == '>' || cmd[lexer->i] == '<')
		add_single_char(cmd, mini, lexer);
	else if (cmd[lexer->i] == '|')
		add_pipe_char(cmd, mini, lexer);
	else
		return (0);
	return (1);
}

int	lexersplit_1(char *cmd, t_mini *mini, t_lexer *lexer)
{
	int		words;

	words = count_words_lex(cmd, lexer);
	if (lexer->flag != 0)
	{
		ft_error(lexer->flag);
		return (-1);
	}
	mini->toks = ft_calloc(sizeof(char *), (words + 1));
	if (!mini->toks)
		return (-1);
	while (cmd[lexer->i])
	{
		mini->toks[lexer->j] = ft_calloc(sizeof(char), 1000);
		if (sub_ifs_lexersplit(cmd, mini, lexer) == 1)
			;
		else
		{
			add_str(cmd, mini, lexer, mini->env);
			lexer->j++;
		}
	}
	mini->toks[lexer->j] = NULL;
	return (0);
}

int	lexersplit(char *cmd, t_mini *mini)
{
	t_lexer	lexer;

	lexer.i = 0;
	lexer.j = 0;
	lexer.k = 0;
	lexer.l = 0;
	lexer.flag = 0;
	if (lexersplit_1(cmd, mini, &lexer) == -1)
	{
		return (-1);
	}
	if (!mini->toks)
		return (0);
	return (1);
}
