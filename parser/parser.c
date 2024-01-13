/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/13 20:32:14 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sub_last_else(t_mini *mini, t_parser *parser, t_cmds *cmds)
{
	if (cmds->cmd == NULL)
	{
		cmds->cmd = ft_strdup(mini->toks[parser->i]);
		cmds->args[0] = ft_strdup(cmds->cmd);
		parser->i++;
	}
	else
	{
		while (mini->toks[parser->i]
			&& ft_strncmp(mini->toks[parser->i], "|", 1)
			&& !is_redirect(mini->toks[parser->i]))
		{
			cmds->args[parser->j] = ft_strdup(mini->toks[parser->i]);
			parser->j++;
			parser->i++;
		}
	}
	cmds->args[parser->j] = NULL;
}

int	sub_parser(t_mini *mini, t_parser *parser, t_cmds *cmds)
{
	if (!ft_strncmp(mini->toks[parser->i], ">>", 2))
	{
		if (add_out_redirect(cmds, mini->toks, parser, 2) == -1)
			return (-1);
	}
	else if (!ft_strncmp(mini->toks[parser->i], ">", 1))
	{
		if (add_out_redirect(cmds, mini->toks, parser, 1) == -1)
			return (-1);
	}
	else if (!ft_strncmp(mini->toks[parser->i], "<<", 2))
	{
		if (add_in_redirect(cmds, mini->toks, parser, 4) == -1)
			return (-1);
	}
	else if (!ft_strncmp(mini->toks[parser->i], "<", 1))
	{
		if (add_in_redirect(cmds, mini->toks, parser, 3) == -1)
			return (-1);
	}
	else
		sub_last_else(mini, parser, cmds);
	return (1);
}

void	ft_increment(t_parser *parser)
{
	parser->i++;
	parser->k++;
	parser->l++;
}

int	parser(t_mini *mini)
{
	t_parser	parser;
	t_cmds		*cmds;
	t_cmds		*head;

	cmds = ft_calloc(sizeof(t_cmds), 1);
	head = cmds;
	init_parser(&parser, mini, cmds);
	while (mini->toks[parser.i])
	{
		if (ft_strncmp(mini->toks[parser.i], "|", 1) == 0)
		{
			if (mini->toks[parser.i + 1] == NULL)
				return (-1);
			mini->cmds_count++;
			cmds->next = ft_calloc(sizeof(t_cmds), 1);
			cmds = cmds->next;
			ft_increment(&parser);
			init_cmds(cmds, mini, &parser);
			parser.j = 1;
		}
		else if (sub_parser(mini, &parser, cmds) == -1)
			return (-1);
	}
	mini->cmds = head;
	return (1);
}
