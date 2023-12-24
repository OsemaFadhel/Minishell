/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:16 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/24 22:52:48 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_var(char *tmp, char **env)
{
	int	i;
	int	j;
	int	k;
	char *env_var;

	i = 0;
	k = 0;
	j = ft_strlen(tmp);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], tmp, j) == 0)
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			j++;
			env_var = malloc(sizeof(char) * ft_strlen(env[i]) - j + 1);
			while (env[i][j] != '\0')
			{
				env_var[k] = env[i][j];
				j++;
				k++;
			}
			env_var[k] = '\0';
			return (env_var);
		}
		i++;
	}
	return (NULL);
}

char *get_env_name(char *cmd, int i)
{
	char *env_var;

	int l;

	l = 0;
	env_var = malloc(sizeof(char) * 1000);
	while (cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '\"' && cmd[i] != '=')
	{
		env_var[l] = cmd[i];
		i++;
		l++;
	}
	env_var[l] = '=';
	env_var[++l] = '\0';
	return (env_var);
}

//add str found inside double quotes
int	add_str_dquot(char *cmd, char **toks, int i, int j, char **env)
{
	int	k;
	int l;
	int post;
	char *env_var;
	char *var;

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
				l = 0;
				env_var = get_env_name(cmd, i);
				post =  ft_strlen(env_var) - 1;
				var = get_env_var(env_var, env);
				if (var != NULL)
				{
					while (var[l] != '\0')
					{
						toks[j][k] = var[l];
						l++;
						k++;
					}
				}
				free(env_var);
				free(var);
				i += post;
			}
			else
			{
				toks[j][k] = cmd[i];
				i++;
				k++;
			}
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
int	add_str(char *cmd, char **toks, int i, int j, char **env)
{
	int	k;
	int l;
	int post;
	char *env_var;
	char *var;

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
		if (cmd[i] == '$')
		{
			i++;
			l = 0;
			env_var = get_env_name(cmd, i);  // add check for exit status $?
			post =  ft_strlen(env_var) - 1;
			var = get_env_var(env_var, env);
			if (var != NULL)
			{
				while (var[l] != '\0')
				{
					toks[j][k] = var[l];
					l++;
					k++;
				}
			}
			free(env_var);
			free(var);
			i += post;
		}
		if ((cmd[i] == '>' && cmd[i + 1] == '>') | (cmd[i] == '<' && cmd[i + 1] == '<'))
			break;
		if (cmd[i] == '>' | cmd[i] == '<')
			break;
		else
		{
			toks[j][k] = cmd[i];
			i++;
			k++;
		}
	}
	toks[j][k] = '\0';
	return (i);
}
