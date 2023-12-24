/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/24 23:13:05 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

void	init_cmds(t_cmds *cmds)
{
	cmds->cmd = NULL;
	cmds->args = NULL;
	cmds->mredirect = malloc(sizeof(t_redirect));
    if (!cmds->redirect)
        return ;
    cmds->redirect->infile = NULL;
    cmds->redirect->outfile = NULL;
    cmds->redirect->delimiter = NULL;
    cmds->redirect->redirect_type = 0;
    cmds->fdi = 0;
    cmds->fdo = 1;
	cmds->next = NULL;
}

int	parser(t_mini *mini)
{
    int		i;
    int		j;
    int		k;
    int     red;
    t_cmds	*cmds;

    i = 0;
    j = 0;
    k = 0;
    red = 0;
    cmds = malloc(sizeof(t_cmds));
    if (!cmds)
        return (-1);
    init_cmds(cmds);
    while (mini->toks[i] != NULL)
    {
        if (strcmp(mini->toks[i], "|") == 0)
        {
            mini->cmds_count++;
            cmds->next = malloc(sizeof(t_cmds));
            if (!cmds->next)
                return (-1);
            cmds = cmds->next;
            init_cmds(cmds);
            j = 0;
            k = 0;
        }
        else if (strcmp(mini->toks[i], ">") == 0)
        {
            cmds->redirect->outfile = mini->toks[i + 1];
            cmds->redirect->redirect_type = 1;
            i += 2;
        }
        else if (strcmp(mini->toks[i], ">>") == 0)
        {
            cmds->redirect->outfile = mini->toks[i + 1];
            cmds->redirect->redirect_type = 2;
            i += 2;
        }
        else if (strcmp(mini->toks[i], "<") == 0)
        {
            cmds->redirect->infile = mini->toks[i + 1];
            cmds->redirect->redirect_type = 3;
            i += 2;
        }
        else if (strcmp(mini->toks[i], "<<") == 0)
        {
            cmds->redirect->delimiter = mini->toks[i + 1];
            cmds->redirect->redirect_type = 4;
            i += 2;
        }
        else
        {
            if (cmds->cmd == NULL)
                cmds->cmd = mini->toks[i];
            else
            {
                cmds->args = malloc(sizeof(char *) * 1000);
                if (!cmds->args)
                    return (-1);
                while (mini->toks[i] != NULL && strcmp(mini->toks[i], "|") != 0 && strcmp(mini->toks[i], ">") != 0 && strcmp(mini->toks[i], ">>") != 0 && strcmp(mini->toks[i], "<") != 0 && strcmp(mini->toks[i], "<<") != 0)
                {
                    cmds->args[j] = mini->toks[i];
                    j++;
                    i++;
                }
                cmds->args[j] = NULL;
            }
        }
        i++;
    }
    return (0);
}
