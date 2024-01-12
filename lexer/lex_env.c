/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:23:08 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/12 19:27:52 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_env2(t_mini *mini, t_lexer *lexer, char *cmd)
{
	int		post;
	char	*env_var;
	char	*var;
	int		l;

	l = 0;
	env_var = get_env_name(cmd, lexer->i);
	post = ft_strlen(env_var) - 1;
	var = get_env_var(env_var, mini->env);
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
	return (post);
}

int	add_env(t_mini *mini, t_lexer *lexer, char *cmd)
{
	int		post;
	char	*var;
	int		l;

	l = 0;
	lexer->i++;
	if (cmd[lexer->i] == '?')
	{
		var = ft_itoa(g_exit_status);
		while (var[l] != '\0')
		{
			mini->toks[lexer->j][lexer->k] = var[l];
			l++;
			lexer->k++;
		}
		free(var);
		return (1);
	}
	else
	{
		post = add_env2(mini, lexer, cmd);
		return (post);
	}
}

char	*get_env_var(char *tmp, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*env_var;

	i = -1;
	k = -1;
	j = ft_strlen(tmp);
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], tmp, j) == 0)
		{
			env_var = malloc(sizeof(char) * ft_strlen(env[i]) - j + 1);
			while (env[i][j] != '\0')
			{
				env_var[++k] = env[i][j];
				j++;
			}
			env_var[++k] = '\0';
			return (env_var);
		}
	}
	return (NULL);
}

char	*get_env_name(char *cmd, int i)
{
	char	*env_var;
	int		l;

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
