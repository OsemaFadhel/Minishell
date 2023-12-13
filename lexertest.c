/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexertest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:53 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/13 15:15:36 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (check_closed_dquotes(cmd, i) == 0)
			{
				i++;
				while (cmd[i] != '\"')
					i++;
				words++;
				i++;
			}
			else
			{
				i++;
				words++;
			}
		}
		else if (cmd[i] == '\'')
		{
			if (check_closed_quotes(cmd, i) == 0)
			{
				i++;
				while (cmd[i] != '\'')
					i++;
				words++;
				i++;
			}
			else
			{
				i++;
				words++;
			}
		}
		else
		{
			while (cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '\"' && cmd[i] != '\'')
				i++;
			words++;
		}
	}
	printf("words = %d\n", words);
	return (words);
}

char	**lexersplit_1(char *cmd) //split cmd into tokens taking care of spaces and quotes. anything inside quotes count as one word
{
	int		i;
	int		j;
	int		k;
	char	**toks;
	int		words;

	i = 0;
	j = 0;
	k = 0;
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
			if (check_closed_dquotes(cmd, i) == 0)
			{
				toks[j][k] = '\"';
				//printf("toks[%i][%i] = %c\n", j, k, toks[j][k]);
				k++;
				i++;
				while (cmd[i] != '\"')
				{
					toks[j][k] = cmd[i];
					//printf("toks[%i][%i] = %c\n", j, k, toks[j][k]);
					i++;
					k++;
				}
				toks[j][k] = '\"';
				k++;
				//printf("toks[%i][%i] = %c\n", j, k, toks[j][k]);
			}
			else
				toks[j][k] = '\"';
			toks[j][k] = '\0';
			j++;
			k = 0;
			i++;
		}
		else if (cmd[i] == '\'')
		{
			if (check_closed_quotes(cmd, i) == 0)
			{
				toks[j][k] = '\'';
				//printf("toks[%i][%i] = %c\n", j, k, toks[j][k]);
				k++;
				i++;
				while (cmd[i] != '\'')
				{
					toks[j][k] = cmd[i];
					//printf("toks[%i][%i] = %c\n", j, k, toks[j][k]);
					i++;
					k++;
				}
				toks[j][k] = '\'';
				k++;
				//printf("toks[%i][%i] = %c\n", j, k, toks[j][k]);
			}
			else
				toks[j][k] = '\'';
			toks[j][k] = '\0';
			j++;
			k = 0;
			i++;
		}
		else
		{
			while (cmd[i] != ' ' && cmd[i] != '\0')
			{
				if (cmd[i] == '\"' || cmd[i] == '\'')
				{
					if(cmd[i] == '\"' && check_closed_dquotes(cmd, i) == 0)
						break;
					else if (cmd[i] == '\'' && check_closed_quotes(cmd, i) == 0)
						break;
				}
				toks[j][k] = cmd[i];
				i++;
				k++;
			}
			toks[j][k] = '\0';
			j++;
			k = 0;
		}
		//printf("toks[%i] = %s\n", j - 1, toks[j - 1]);
	}
	toks[j] = NULL;
	return (toks);
}

int	lexersplit(char *cmd, t_mini *mini)
{
	int	i;

	i = 0;

	mini->toks = lexersplit_1(cmd);
	if (!mini->toks)
		return (1);
	while (mini->toks[i])
	{
		printf("lexer tok = %s\n", mini->toks[i]);
		i++;
	}
	return (0);
}

// split per virgolette. includere tutto quello dentro in un unico token, incluso virgolette
//
