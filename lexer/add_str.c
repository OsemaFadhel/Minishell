/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:16 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/10 19:18:16 by ofadhel          ###   ########.fr       */
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
int	add_str_dquot(char *cmd, t_mini *mini, t_lexer *lexer, char **env)
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
			mini->toks[lexer->j][lexer->k] = '\b';
			lexer->k++;
		}
		lexer->i++;
		while (cmd[lexer->i] != '\"')
		{
			if (cmd[lexer->i] == '$')
			{
				lexer->i++;
				l = 0;
				env_var = get_env_name(cmd, lexer->i);
				post =  ft_strlen(env_var) - 1;
				var = get_env_var(env_var, env);
				if (var != NULL)
				{
					while (var[l] != '\0')
					{
						mini->toks[lexer->j][lexer->k] = var[l];
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
				mini->toks[lexer->j][lexer->k] = cmd[lexer->i];
				lexer->k++;
				lexer->i++;
			}
		}
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

//add str found inside single quotes
int add_str_quot(char *cmd, t_mini *mini, t_lexer *lexer)
{
	int	k;

	k = 0;
	if (check_closed_quotes(cmd, lexer->i) == 0)
	{
		if (cmd[lexer->i - 1] != ' ' && cmd[lexer->i - 1] != '\0')
		{
			mini->toks[lexer->j][k] = '\b';
			k++;
		}
		lexer->i++;
		while (cmd[lexer->i] != '\'')
		{
			mini->toks[lexer->j][k] = cmd[lexer->i];
			lexer->i++;
			k++;
		}
	}
	else
	{
		mini->toks[lexer->j][k] = '\'';
		k++;
	}
	mini->toks[lexer->j][k] = '\0';
	lexer->i++;
	return (lexer->i);

}

//add str  found outside quotes
int	add_str(char *cmd, t_mini *mini, t_lexer *lexer, char **env)
{
	int	k;
	int l;
	int post;
	char *env_var;
	char *var;

	k = 0;
	while (cmd[lexer->i] != ' ' && cmd[lexer->i] != '\0')
	{
		if (lexer->i > 0)
		{
			if ((cmd[lexer->i - 1] == '\"' || cmd[lexer->i - 1] == '\'') && k == 0) //add in the expander, maybe this not; only the quotes
			{
				mini->toks[lexer->j][k] = '\b';
				k++;
			}
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
					mini->toks[lexer->j][k] = var[l];
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
			mini->toks[lexer->j][k] = cmd[lexer->i];
			lexer->i++;
			k++;
		}
	}
	mini->toks[lexer->j][k] = '\0';
	return (lexer->i);
}
