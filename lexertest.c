/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexertest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:53 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/28 15:58:26 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	splittare prima parola = comando, e poi il resto tutto unico arg
	quindi tok[0] = comando, tok[1] = argomento
	se c'è un pipe, allora tok[0] = comando, tok[1] = argomento, tok[2] = comando, tok[3] = argomento
	oppure tok[0] = comando, tok[1] = argomento, tok[2] = pipe, tok[3] = comando, tok[4] = argomento
	tenere conto delle redirect, pensare a una soluzione
*/

/*char	**lexersplit_1(char *cmd, t_mini *mini)
{

}*/

int	lexersplit(char *cmd, t_mini *mini)
{
	int	i;

	i = 0;

	mini->toks = ft_split(cmd, ' ');
	if (!mini->toks)
		return (1);
	/*while (mini->toks[i])
	{
		printf("%s\n", mini->toks[i]);
		i++;
	}*/
	return (0);
}

// split per virgolette. includere tutto quello dentro in un unico token, incluso virgolette
//
