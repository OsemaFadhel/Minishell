/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:16 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/12 00:41:48 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	str_dquot2(char *cmd, t_mini *mini, t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		if (cmd[lexer->i - 1] != ' ' && cmd[lexer->i - 1] != '\0')
		{
			mini->toks[lexer->j][lexer->k] = '\b';
			lexer->k++;
		}
	}
	lexer->i++;
	while (cmd[lexer->i] != '\"')
	{
		if (cmd[lexer->i] == '$')
			lexer->i += add_env(mini, lexer, cmd);
		else
		{
			mini->toks[lexer->j][lexer->k] = cmd[lexer->i];
			lexer->k++;
			lexer->i++;
		}
	}
	return (1);
}

int	add_str_dquot(char *cmd, t_mini *mini, t_lexer *lexer, char **env)
{
	int	flag;

	lexer->k = 0;
	if (check_closed_dquotes(cmd, lexer->i, lexer) == 0)
	{
		flag = str_dquot2(cmd, mini, lexer);
		if (flag == 0)
			return (0);
	}
	else
	{
		mini->toks[lexer->j][lexer->k] = '\"';
		lexer->k++;
	}
	mini->toks[lexer->j][lexer->k] = '\0';
	lexer->i++;
	return (lexer->i);
}

int	add_str_quot(char *cmd, t_mini *mini, t_lexer *lexer)
{
	lexer->k = 0;
	if (check_closed_quotes(cmd, lexer->i, lexer) == 0)
	{
		if (cmd[lexer->i - 1] != ' ' && cmd[lexer->i - 1] != '\0')
		{
			mini->toks[lexer->j][lexer->k] = '\b';
			lexer->k++;
		}
		lexer->i++;
		while (cmd[lexer->i] != '\'')
		{
			mini->toks[lexer->j][lexer->k] = cmd[lexer->i];
			lexer->i++;
			lexer->k++;
		}
	}
	else
	{
		mini->toks[lexer->j][lexer->k] = '\'';
		lexer->k++;
	}
	mini->toks[lexer->j][lexer->k] = '\0';
	lexer->i++;
	return (lexer->i);
}

int	add_str2(char *cmd, t_mini *mini, t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		if ((cmd[lexer->i - 1] == '\"'
				|| cmd[lexer->i - 1] == '\'') && lexer->k == 0)
		{
			mini->toks[lexer->j][lexer->k] = '\b';
			lexer->k++;
		}
	}
	if (cmd[lexer->i] == '\"' || cmd[lexer->i] == '\'')
	{
		if (cmd[lexer->i] == '\"'
			&& check_closed_dquotes(cmd, lexer->i, lexer) == 0)
			return (0);
		else if (cmd[lexer->i] == '\''
			&& check_closed_quotes(cmd, lexer->i, lexer) == 0)
			return (0);
	}
	if (cmd[lexer->i] == '$')
		lexer->i += add_env(mini, lexer, cmd) - 1;
	if ((cmd[lexer->i] == '>' && cmd[lexer->i + 1] == '>')
		|| (cmd[lexer->i] == '<' && cmd[lexer->i + 1] == '<'))
		return (0);
	return (1);
}

//add str  found outside quotes
int	add_str(char *cmd, t_mini *mini, t_lexer *lexer, char **env)
{
	int	flag;

	lexer->k = 0;
	while (cmd[lexer->i] != ' ' && cmd[lexer->i] != '\0')
	{
		flag = add_str2(cmd, mini, lexer);
		if (flag == 0)
			break ;
		else if (flag == -1)
			return (-1);
		if (cmd[lexer->i] == '>' || cmd[lexer->i] == '<')
			break ;
		if (cmd[lexer->i] == '|')
			break ;
		else
		{
			mini->toks[lexer->j][lexer->k] = cmd[lexer->i];
			lexer->i++;
			lexer->k++;
		}
	}
	mini->toks[lexer->j][lexer->k] = '\0';
	return (lexer->i);
}
