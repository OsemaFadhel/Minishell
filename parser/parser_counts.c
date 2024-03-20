/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_counts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:19:55 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:37 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_red_arg(t_mini *mini, int i)
{
	if (!ft_strncmp(mini->toks[i], ">>", 2))
		i += 2;
	else if (!ft_strncmp(mini->toks[i], ">", 1))
		i += 2;
	else if (!ft_strncmp(mini->toks[i], "<<", 2))
		i += 2;
	else if (!ft_strncmp(mini->toks[i], "<", 1))
		i += 2;
	return (i);
}

int	count_args(t_mini *mini, t_parser *parser)
{
	int	count;

	count = 0;
	while (mini->toks[parser->l])
	{
		if (ft_strncmp(mini->toks[parser->l], "|", 1) == 0)
			break ;
		else if (is_redirect(mini->toks[parser->l]))
		{
			parser->l = count_red_arg(mini, parser->l);
			if (mini->toks[parser->l - 1] == NULL)
				break ;
		}
		else
		{
			while (mini->toks[parser->l]
				&& ft_strncmp(mini->toks[parser->l], "|", 1)
				&& !is_redirect(mini->toks[parser->l]))
			{
				count++;
				parser->l++;
			}
		}
	}
	return (count);
}

int	count_redirect(t_mini *mini, t_parser *parser)
{
	int	count;

	count = 0;
	while (mini->toks[parser->k] && ft_strncmp(mini->toks[parser->k], "|", 1))
	{
		if (!ft_strncmp(mini->toks[parser->k], ">>", 2))
			count++;
		else if (!ft_strncmp(mini->toks[parser->k], ">", 1))
			count++;
		else if (!ft_strncmp(mini->toks[parser->k], "<<", 2))
			count++;
		else if (!ft_strncmp(mini->toks[parser->k], "<", 1))
			count++;
		parser->k++;
	}
	return (count);
}
