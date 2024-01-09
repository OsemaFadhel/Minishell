/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:07:00 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 18:45:29 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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

int	add_str(char *cmd, char **toks, t_lexer *lexer, char **env)
{
	int	k;
	int l;
	int post;
	char *env_var;
	char *var;

	k = 0;
	while (cmd[lexer->i] != ' ' && cmd[lexer->i] != '\0')
	{
		if (cmd[lexer->i - 1] == '\"' || cmd[lexer->i - 1] == '\'') //add in the expander, maybe this not; only the quotes
		{
			toks[lexer->j][k] = '\b';
			k++;
		}
		if (cmd[lexer->i] == '\"' || cmd[lexer->i] == '\'')
		{
			if(cmd[lexer->i] == '\"' && check_closed_dquotes(cmd, lexer->i) == 0)
				break;
			else if (cmd[lexer->i] == '\'' && check_closed_quotes(cmd, lexer->i) == 0)
				break;
		}
		if (cmd[lexer->i] == '$')
		{
			lexer->i++;
			l = 0;
			env_var = get_env_name(cmd, lexer->i);  // add check for exit status $?
			post =  ft_strlen(env_var) - 1;
			var = get_env_var(env_var, env);
			if (var != NULL)
			{
				while (var[l] != '\0')
				{
					toks[lexer->j][k] = var[l];
					l++;
					k++;
				}
			}
			free(env_var);
			free(var);
			lexer->i += post;
		}
		if ((cmd[lexer->i] == '>' && cmd[lexer->i + 1] == '>') | (cmd[lexer->i] == '<' && cmd[lexer->i + 1] == '<'))
			break;
		if (cmd[lexer->i] == '>' | cmd[lexer->i] == '<')
			break;
		if (cmd[lexer->i] == '|')
			break;
		else
		{
			toks[lexer->j][k] = cmd[lexer->i];
			lexer->i++;
			k++;
		}
	}
	toks[lexer->j][k] = '\0';
	return (lexer->i);
}

int	count_size_tok(char *cmd)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		else if (sub_ifs_lexersplit(cmd, lexer, &i) == 1);
		else
			size = add_str(cmd, lexer, &i);
	}

}
