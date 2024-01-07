/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:53 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 19:44:14 by ofadhel          ###   ########.fr       */
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
void	add_pipe_char(char *cmd, char **toks, t_lexer *lexer)
{
	toks[lexer->j][0] = cmd[lexer->i];
	toks[lexer->j][1] = '\0';
	lexer->i++;
	lexer->j++;
}

void	add_single_char(char *cmd, char **toks, t_lexer *lexer)
{
	toks[lexer->j][0] = cmd[lexer->i];
	toks[lexer->j][1] = '\0';
	lexer->i++;
	lexer->j++;
}

void	add_redirect(char *cmd, char **toks, t_lexer *lexer)
{
	toks[lexer->j][0] = cmd[lexer->i];
	toks[lexer->j][1] = cmd[lexer->i + 1];
	toks[lexer->j][2] = '\0';
	lexer->i += 2;
	lexer->j++;
}

int	sub_ifs_lexersplit(char *cmd, t_mini *mini, t_lexer *lexer, char **toks)
{
	if (cmd[lexer->i] == '\"')
	{
		lexer->i = add_str_dquot(cmd, toks, lexer, mini->env);
		lexer->j++;
	}
	else if (cmd[lexer->i] == '\'')
	{
		lexer->i = add_str_quot(cmd, toks, lexer);
		lexer->j++;
	}
	else if ((cmd[lexer->i] == '>' && cmd[lexer->i + 1] == '>')
			|| (cmd[lexer->i] == '<' && cmd[lexer->i + 1] == '<'))
		add_redirect(cmd, toks, lexer);
	else if (cmd[lexer->i] == '>' | cmd[lexer->i] == '<')
		add_single_char(cmd, toks, lexer);
	else if (cmd[lexer->i] == '|')
		add_pipe_char(cmd, toks, lexer);
	else
		return (0);
	return (1);
}
//split cmd into tokens taking care of spaces and quotes. anything inside quotes count as one word
char	**lexersplit_1(char *cmd, t_mini *mini, t_lexer *lexer)
{
	char	**toks;
	int		words;

	words = count_words_lex(cmd);
	toks = malloc(sizeof(char *) * (words + 1));
	if (!toks)
		return (NULL);
	while (cmd[lexer->i])
	{
		toks[lexer->j] = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
		if (cmd[lexer->i] == ' ')
			lexer->i++;
		else if (sub_ifs_lexersplit(cmd, mini, lexer, toks) == 1);
		else
		{
			lexer->i = add_str(cmd, toks, lexer, mini->env);
			lexer->j++;
		}
	}
	toks[lexer->j] = NULL;
	return (toks);
}

int	lexersplit(char *cmd, t_mini *mini)
{
	t_lexer	lexer;

	lexer.i = 0;
	lexer.j = 0;
	lexer.k = 0;
	lexer.l = 0;
	mini->toks = lexersplit_1(cmd, mini, &lexer);
	free(cmd);
	if (!mini->toks)
		return (0);
	return (1);
}
