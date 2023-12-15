/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:16 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/15 17:02:06 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_var(char *var, char **envp)
{
	int	i;
	int	j;
	char	*env_var;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		while (envp[i][j] != '=')
			j++;
		if (ft_strncmp(envp[i], var, j) == 0)
		{
			if (envp[i][j + 1] != '=')
			{
				env_var = ft_strdup("");
				return (env_var);
			}
			env_var = ft_strdup(envp[i] + j + 1);
			return (env_var);
		}
		i++;
		j = 0;
	}
	return (NULL);
}


//add str found inside double quotes
int	add_str_dquot(char *cmd, char **toks, int i, int j, char **envp)
{
	int	k;
	char *tmp;

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
				i++;
				tmp = malloc(sizeof(char) * 100);
				int l = 0;
				while (cmd[i] != ' ')
				{
					tmp[l] = cmd[i];
					i++;
				}
				tmp[l] = '\0';
				char *env_var = get_env_var(tmp, envp);
				int m = 0;
				while (env_var[m] != '\0')
				{
					toks[j][k] = env_var[m];
					m++;
					k++;
				}
				free(env_var);
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
