/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:16 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/05 03:13:01 by ofadhel          ###   ########.fr       */
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
int	add_str_dquot(char *cmd, char **toks, t_lexer *lexer, char **env)
{
	int	k;
	int l;
	int post;
	char *env_var;
	char *var;

	lexer->k = 0;
	if (check_closed_dquotes(cmd, lexer->i) == 0) //expander change env var $
	{
		if (cmd[lexer->i - 1] != ' ' && cmd[lexer->i - 1] != '\0') //maybe implent in the expander so firtst we can check the quotes for the env $ thenk remove the spaces
		{
			toks[lexer->j][lexer->k] = '\b';
			lexer->k++;
		}
		//toks[j][lexer->k] = '\"';
		//lexer->k++;
		lexer->i++;
		while (cmd[lexer->i] != '\"')
		{
			if (cmd[lexer->i] == '$')
			{
				lexer->j++;
				l = 0;
				env_var = get_env_name(cmd, lexer->i);
				post =  ft_strlen(env_var) - 1;
				var = get_env_var(env_var, env);
				if (var != NULL)
				{
					while (var[l] != '\0')
					{
						toks[lexer->j][lexer->k] = var[l];
						l++;
						lexer->k++;
					}
				}
				free(env_var);
				free(var);
				lexer->i += post;
			}
			else
			{
				toks[lexer->j][lexer->k] = cmd[lexer->i];
				lexer->j++;
				lexer->k++;
			}
		}
		//toks[j][lexer->k] = '\"';
		//lexer->k++;
	}
	else
	{
		toks[lexer->j][lexer->k] = '\"';
		lexer->k++;
	}
	toks[lexer->j][lexer->k] = '\0';
	lexer->i++;
	return (lexer->i);
}

//add str found inside single quotes
int add_str_quot(char *cmd, char **toks, t_lexer *lexer)
{
	int	k;

	k = 0;
	if (check_closed_quotes(cmd, lexer->i) == 0)
	{
		if (cmd[lexer->i - 1] != ' ' && cmd[lexer->i - 1] != '\0')
		{
			toks[lexer->j][k] = '\b';
			k++;
		}
		//toks[j][k] = '\'';
		//k++;
		lexer->i++;
		while (cmd[lexer->i] != '\'')
		{
			toks[lexer->j][k] = cmd[lexer->i];
			lexer->i++;
			k++;
		}
		//toks[j][k] = '\'';
		//k++;
	}
	else
	{
		toks[lexer->j][k] = '\'';
		k++;
	}
	toks[lexer->j][k] = '\0';
	lexer->i++;
	return (lexer->i);

}

void	change_env_v(char *cmd, char **toks, t_lexer *lexer, char **env)
{
	int	l;
	int post;
	char *env_var;
	char *var;

	if (cmd[lexer->i] == '$')
	{
		lexer->j++;
		lexer->l = 0;
		env_var = get_env_name(cmd, lexer->i);
		post =  ft_strlen(env_var) - 1;
		var = get_env_var(env_var, env);
		if (var != NULL)
		{
			while (var[lexer->l] != '\0')
			{
				toks[lexer->j][lexer->k] = var[lexer->l];
				lexer->l++;
				lexer->k++;
			}
		}
		free(env_var);
		free(var);
		lexer->i += post;
	}
}

//add str  found outside quotes
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
