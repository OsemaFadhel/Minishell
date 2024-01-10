/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 00:42:27 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/10 20:33:22 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void free_redirect(t_redirect *redirect)
{
	int i;

	i = -1;
	while (redirect[++i].redirect_type != 0)
	{
		if (redirect[i].redirect_type == 1 || redirect[i].redirect_type == 2)
			free(redirect[i].outfile);
		else if (redirect[i].redirect_type == 3 || redirect[i].redirect_type == 4)
			free(redirect[i].infile);
	}
	free(redirect);
}

void free_cmds_list(t_cmds *head)
{
	t_cmds *tmp;
	int i;

	i = 0;
	while (head)
	{
		tmp = head;
		free(tmp->cmd);
		if (tmp->args)
		{
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		};
		free_redirect(tmp->redirect);
		head = head->next;
		free(tmp);
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_mini *mini, char *input) // free cmds line
{
	ft_free_array(mini->toks);
	free_cmds_list(mini->cmds);
	//free(input);
}
