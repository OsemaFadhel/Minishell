/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:44:27 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/13 20:34:52 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(char *str)
{
	if (str[0] == '>' || str[0] == '<')
		return (1);
	return (0);
}

int	add_out_redirect(t_cmds *cmds, char **toks, t_parser *parser, int type)
{
	if (!toks[parser->i + 1] || ft_strncmp(toks[parser->i + 1], "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (toks[parser->i + 1][0] == '>' || toks[parser->i + 1][0] == '<')
		parser->i++;
	else
	{
		cmds->redirect[cmds->redirect_count].outfile
			= ft_strdup(toks[parser->i + 1]);
		cmds->redirect[cmds->redirect_count].redirect_type = type;
		cmds->redirect_count++;
		cmds->out = 1;
		parser->i += 2;
	}
	return (parser->i);
}

int	add_in_redirect(t_cmds *cmds, char **toks, t_parser *parser, int type)
{
	if (!toks[parser->i + 1] || ft_strncmp(toks[parser->i + 1], "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (toks[parser->i + 1][0] == '>' || toks[parser->i + 1][0] == '<')
		parser->i++;
	else
	{
		cmds->redirect[cmds->redirect_count].infile
			= ft_strdup(toks[parser->i + 1]);
		cmds->redirect[cmds->redirect_count].redirect_type = type;
		cmds->redirect_count++;
		cmds->in = 1;
		parser->i += 2;
	}
	return (parser->i);
}
