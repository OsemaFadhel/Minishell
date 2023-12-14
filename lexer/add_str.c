/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:16 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/14 13:38:33 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_env_var(char *cmd, char **toks, int i, int j, char **envp)
{
	//to do: check if the env var is valid
}


//add str found inside double quotes
int	add_str_dquot(char *cmd, char **toks, int i, int j, char **envp)
{
	int	k;

	k = 0;
	if (check_closed_dquotes(cmd, i) == 0) //expander change env var $
	{
		if (cmd[i - 1] != ' ' && cmd[i - 1] != '\0') //maybe implent in the expander so firtst we can check the quotes for the env $ thenk remove the spaces
		{
			toks[j][k] = '\b';
			k++;
		}
		//toks[j][k] = '\"';
		//k++;
		i++;
		while (cmd[i] != '\"')
		{
			if (cmd[i] == '$')
			{
				i = add_env_var(cmd, toks, i, j, envp); // to check if the env var is valid
				k = ft_strlen(toks[j]);
			}
			toks[j][k] = cmd[i];
			i++;
			k++;
		}
		//toks[j][k] = '\"';
		//k++;
	}
	else
	{
		toks[j][k] = '\"';
		k++;
	}
	toks[j][k] = '\0';
	i++;
	return (i);
}

//add str found inside single quotes
int add_str_quot(char *cmd, char **toks, int i, int j)
{
	int	k;

	k = 0;
	if (check_closed_quotes(cmd, i) == 0)
	{
		if (cmd[i - 1] != ' ' && cmd[i - 1] != '\0')
		{
			toks[j][k] = '\b';
			k++;
		}
		//toks[j][k] = '\'';
		//k++;
		i++;
		while (cmd[i] != '\'')
		{
			toks[j][k] = cmd[i];
			i++;
			k++;
		}
		//toks[j][k] = '\'';
		//k++;
	}
	else
	{
		toks[j][k] = '\'';
		k++;
	}
	toks[j][k] = '\0';
	i++;
	return (i);
}

//add str  found outside quotes
int	add_str(char *cmd, char **toks, int i, int j, char **envp)
{
	int	k;

	k = 0;
	while (cmd[i] != ' ' && cmd[i] != '\0')
	{
		if (cmd[i - 1] == '\"' || cmd[i - 1] == '\'') //add in the expander, maybe this not; only the quotes
		{
			toks[j][k] = '\b';
			k++;
		}
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
	return (i);
}
