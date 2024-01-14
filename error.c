/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:53:18 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/14 16:11:09 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_inside_words(char *cmd, int i, t_lexer *lexer)
{
	int	j;

	j = i + 1;
	i++;
	while (cmd[i] && cmd[i] != '|')
		i++;
	while (cmd[j] && cmd[j] != '|')
	{
		if (j < i)
		{
			if (ft_isalnum(cmd[j]) != 0)
				return (0);
		}
		j++;
	}
	lexer->flag = 3;
	return (-1);
}

int	check_error2(char *cmd, t_lexer *lexer, int i)
{
	if ((cmd[i] == '>' && cmd[i + 1] == '>')
		|| (cmd[i] == '<' && cmd[i + 1] == '<'))
	{
		if (check_inside_words(cmd, i + 1, lexer) == -1)
			return (-1);
	}
	else if (cmd[i] == '>' || cmd[i] == '<')
	{
		if (check_inside_words(cmd, i, lexer) == -1)
			return (-1);
	}
	else
		return (0);
	return (1);
}

int	check_only_spaces(char *cmd, int i, t_lexer *lexer)
{
	if (cmd[i] == ' ')
	{
		while (cmd[i] == ' ' && cmd[i] != '\0' && cmd[i] != '|')
		{
			i++;
			if (cmd[i] == '\0' || cmd[i] == '|')
			{
				lexer->flag = 5;
				return (-1);
			}
		}
	}
	return (0);
}

int	check_error(char *cmd, t_lexer *lexer)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	flag = check_only_spaces(cmd, i, lexer);
	while (cmd[i])
	{
		flag = check_error2(cmd, lexer, i);
		if (flag == -1)
			break ;
		else if (flag == 1)
			;
		else if (cmd[i] == '|')
		{
			if (check_inside_words(cmd, i, lexer) == -1)
			{
				printf("Error: syntax er\n");
				lexer->flag = 4;
				return (-1);
			}
		}
		i++;
	}
	return (lexer->flag);
}

int	ft_error(int flag)
{
	if (flag == 1)
		printf("Error: unclosed quotes\n");
	if (flag == 2)
		printf("Error: No such file or directory\n");
	if (flag == 3)
		printf("Error: expecting file name after redirection\n");
	if (flag == 4)
		printf("Error: syntax error near unexpected token\n");
	if (flag == 5)
		printf("Error: empty command line\n");
	g_exit_status = 2;
	return (0);
}
