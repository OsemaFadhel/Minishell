/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 00:42:27 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 23:16:54 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_redirect(t_cmds *tmp)
{
	int	i;

	i = -1;
	if (!tmp->redirect->redirect_type || !tmp->redirect)
		return ;
	while (tmp->redirect[++i].redirect_type != 0)
	{
		if (tmp->redirect[i].infile)
			free(tmp->redirect[i].infile);
		if (tmp->redirect[i].outfile)
			free(tmp->redirect[i].outfile);
	}
	free(tmp->redirect);
}

void	free_cmds_list(t_cmds *head)
{
	t_cmds	*tmp;
	int		i;

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
		}
		free_redirect(tmp);
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
	if (mini->fdin != 0)
		close(mini->fdin);
	if (mini->fdout != 1)
		close(mini->fdout);
}
