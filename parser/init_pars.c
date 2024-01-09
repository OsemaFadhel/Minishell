/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:45:05 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 10:45:35 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	init_cmds(t_cmds *cmds, t_mini *mini, t_parser *parser)
{
	cmds->cmd = NULL;
	cmds->args = malloc(sizeof(char *) * (count_args(mini) + 1));
	cmds->redirect = malloc(sizeof(t_redirect) * (count_redirect(mini, parser) + 1));
	cmds->out = 0;
	cmds->in = 0;
	cmds->redirect_count = 0;
	cmds->next = NULL;
}

void	new_cmd(t_mini *mini, t_parser *parser, t_cmds *cmds)
{
	mini->cmds_count++;
	cmds->next = malloc(sizeof(t_cmds));
	cmds = cmds->next;
	parser->k++;
	init_cmds(cmds, mini, parser);
	parser->i++;
	parser->j = 1;
}

void	init_parser(t_parser *parser)
{
	parser->i = 0;
	parser->j = 1;
	parser->k = 0;
}
