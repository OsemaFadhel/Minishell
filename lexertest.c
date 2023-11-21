/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexertest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:53 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/21 18:58:22 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	lexersplit(char *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	mini->toks = ft_split(cmd, ' ');
	if (!mini->toks)
		return (1);
	while (mini->toks[i])
	{
		printf("%s\n", mini->toks[i]);
		i++;
	}
	return (0);
}
