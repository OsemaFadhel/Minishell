/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:53 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/21 15:38:39 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	splittare prima parola = comando, e poi il resto tutto unico arg
	quindi tok[0] = comando, tok[1] = argomento
	se c'è un pipe, allora tok[0] = comando, tok[1] = argomento, tok[2] = comando, tok[3] = argomento
	oppure tok[0] = comando, tok[1] = argomento, tok[2] = pipe, tok[3] = comando, tok[4] = argomento
	tenere conto delle redirect, pensare a una soluzione
*/
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

//split cmd into tokens taking care of spaces and quotes. anything inside quotes count as one word
char	**lexersplit_1(char *cmd, char **env)
{
	int		i;
	int		j;
	char	**toks;
	int		words;

	i = 0;
	j = 0;
	words = count_words(cmd);
	toks = malloc(sizeof(char *) * (words + 1));
	if (!toks)
		return (NULL);
	while (cmd[i])
	{
		toks[j] = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
		if (cmd[i] == ' ')
			i++;
		else if (cmd[i] == '\"')
		{
			i = add_str_dquot(cmd, toks, i, j, env);
			j++;
		}
		else if (cmd[i] == '\'')
		{
			i = add_str_quot(cmd, toks, i, j);
			j++;
		}
		else if ((cmd[i] == '>' && cmd[i + 1] == '>') | (cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			toks[j][0] = cmd[i];
			toks[j][1] = cmd[i + 1];
			toks[j][2] = '\0';
			i += 2;
			j++;
		}
		else if (cmd[i] == '>' | cmd[i] == '<')
		{
			toks[j][0] = cmd[i];
			toks[j][1] = '\0';
			i++;
			j++;
		}
		else
		{
			i = add_str(cmd, toks, i, j, env);
			j++;
		}
	}
	toks[j] = NULL;
	return (toks);
}

int	lexersplit(char *cmd, t_mini *mini)
{
	int	i;

	i = 0;

	mini->toks = lexersplit_1(cmd, mini->env);
	if (!mini->toks)
		return (1);
	while (mini->toks[i])
	{
		printf("lexer tok[%i] = %s\n", i, mini->toks[i]);
		i++;
	}
	return (0);
}

// split per virgolette. includere tutto quello dentro in un unico token, incluso virgolette
//
