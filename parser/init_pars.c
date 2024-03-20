/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:19:50 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:36 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_cmds(t_cmds *cmds, t_mini *mini, t_parser *parser)
{
	cmds->cmd = NULL;
	cmds->args = ft_calloc(sizeof(char *), (count_args(mini, parser) + 1));
	cmds->redirect = ft_calloc(sizeof(t_redirect),
			(count_redirect(mini, parser) + 1));
	cmds->out = 0;
	cmds->in = 0;
	cmds->redirect_count = 0;
	cmds->next = NULL;
}

void	init_parser(t_parser *parser, t_mini *mini, t_cmds *cmds)
{
	parser->i = 0;
	parser->j = 1;
	parser->k = 0;
	parser->l = 0;
	init_cmds(cmds, mini, parser);
}
