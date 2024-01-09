/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 23:14:42 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sub_last_else(t_mini *mini, t_parser *parser, t_cmds *cmds)
{
	if (cmds->cmd == NULL)
	{
		cmds->cmd = ft_strdup(mini->toks[parser->i]);
		cmds->args[parser->j] = ft_strdup(mini->toks[parser->i]);
		parser->i++;
	}
	else
	{
		while (mini->toks[parser->i]
			&& ft_strncmp(mini->toks[parser->i], "|", 1)
			&& !is_redirect(mini->toks[parser->i]))
		{
			cmds->args[parser->j] = ft_strdup(mini->toks[parser->i]);
			parser->i++;
		}
	}
	parser->j++;
	cmds->args[parser->j] = NULL;
}

int	parser(t_mini *mini)
{
	t_parser	parser;
	t_cmds		*cmds;
	t_cmds		*head;

	init_parser(&parser);
	cmds = ft_calloc(sizeof(t_cmds), 1);
	head = cmds;
	init_cmds(cmds, mini, &parser);
	while (mini->toks[parser.i])
	{
		if (ft_strncmp(mini->toks[parser.i], "|", 1) == 0)
		{
			if (mini->toks[parser.i + 1] == NULL)
				return (-1);
			mini->cmds_count++;
			parser.j = 0;
			cmds->next = ft_calloc(sizeof(t_cmds), 1);
			cmds = cmds->next;
			parser.k++;
			init_cmds(cmds, mini, &parser);
			parser.i++;
		}
		else if (!ft_strncmp(mini->toks[parser.i], ">>", 2))
		{
			if (add_out_redirect(cmds, mini->toks, &parser, 2) == -1)
				return (-1);
		}
		else if (!ft_strncmp(mini->toks[parser.i], ">", 1))
		{
			if (add_out_redirect(cmds, mini->toks, &parser, 1) == -1)
				return (-1);
		}
		else if (!ft_strncmp(mini->toks[parser.i], "<<", 2))
		{
			if (add_in_redirect(cmds, mini->toks, &parser, 4) == -1)
				return (-1);
		}
		else if (!ft_strncmp(mini->toks[parser.i], "<", 1))
		{
			if (add_in_redirect(cmds, mini->toks, &parser, 3) == -1)
				return (-1);
		}
		else
			sub_last_else(mini, &parser, cmds);
	}
	mini->cmds = head;
	return (1);
}
