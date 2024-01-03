/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/03 20:32:54 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

/*void    parseRedirection(char **toks, t_cmds *cmd)
{
    int i;

    cmd->redirect_count = 0; // Initialize the count to 0
    i = 0;
    while (toks[i] != NULL && toks[i] != '|')
    {
        if (toks[i][0] == '>')
        {
            cmd->redirect[cmd->redirect_count] = (t_redirect *)malloc(sizeof(t_redirect));
            cmd->redirect[cmd->redirect_count]->redirect_type = 1;
            cmd->redirect[cmd->redirect_count]->outfile = ft_strdup(toks[i + 1]);
            cmd->redirect[cmd->redirect_count]->infile = NULL;
            cmd->redirect[cmd->redirect_count]->appendfile = NULL;
            ++cmd->redirect_count;
            i++;
        }
        else if (toks[i][0] == '>' && toks[i + 1][0] == '>')
        {
            cmd->redirect[cmd->redirect_count] = (t_redirect *)malloc(sizeof(t_redirect));
            cmd->redirect[cmd->redirect_count]->redirect_type = 2;
            cmd->redirect[cmd->redirect_count]->outfile = ft_trdup(toks[i + 2]);
            cmd->redirect[cmd->redirect_count]->infile = NULL;
            cmd->redirect[cmd->redirect_count]->appendfile = NULL;
            ++cmd->redirect_count;
            i++;
        }
        else if (toks[i][0] == '<')
        {
            cmd->redirect[cmd->redirect_count] = (t_redirect *)malloc(sizeof(t_redirect));
            cmd->redirect[cmd->redirect_count]->redirect_type = 3;
            cmd->redirect[cmd->redirect_count]->infile = ft_strdup(toks[i + 1]);
            cmd->redirect[cmd->redirect_count]->outfile = NULL;
            cmd->redirect[cmd->redirect_count]->appendfile = NULL;
            ++cmd->redirect_count;
            i++;
        }
        i++;
    }
} */

void	init_cmds(t_cmds *cmds)
{
	cmds->cmd = NULL;
	cmds->args = malloc(sizeof(char *) * 120);
	cmds->redirect = malloc(sizeof(t_redirect) * 20);
	cmds->next = NULL;
}

void	init_redirect(t_redirect *redirect)
{
	redirect->infile = NULL;
	redirect->outfile = NULL;
	redirect->redirect_type = 0;
}

int	is_redirect(char *str)
{
	if (str[0] == '>' || str[0] == '<')
		return (1);
	return (0);
}

int	parser(t_mini *mini)
{
	int i;
	int j;
	int red_count;
	t_cmds	*cmds;
	t_cmds  *head;

	i = 0;
	j = 1;
	red_count = 0;
	head = cmds = malloc(sizeof(t_cmds));
	init_cmds(cmds);
	while (mini->toks[i])
	{
		if (ft_strncmp(mini->toks[i], "|", 1) == 0)
		{
			mini->cmds_count++;
			cmds->next = malloc(sizeof(t_cmds));
			cmds = cmds->next;
			init_cmds(cmds);
			i++;
		}
		else if (!ft_strncmp(mini->toks[i], ">>", 2))
		{
			init_redirect(&cmds->redirect[red_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1] == "|")
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[red_count].outfile = mini->toks[i + 1];
			cmds->redirect[red_count].redirect_type = 2;
			red_count++;
			i += 2;
		}
		else if (!ft_strncmp(mini->toks[i], ">", 1))
		{
			init_redirect(&cmds->redirect[red_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1] == "|")
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[red_count].outfile = mini->toks[i + 1];
			cmds->redirect[red_count].redirect_type = 1;
			red_count++;
			i += 2;
		}
		else if (!ft_strncmp(mini->toks[i], "<<", 2))
		{
			init_redirect(&cmds->redirect[red_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1] == "|")
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[red_count].infile = mini->toks[i + 1];
			cmds->redirect[red_count].redirect_type = 4;
			red_count++;
			i += 2;
		}
		else if (!ft_strncmp(mini->toks[i], "<", 1))
		{
			init_redirect(&cmds->redirect[red_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1][0] == '|')
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[red_count].infile = mini->toks[i + 1];
			cmds->redirect[red_count].redirect_type = 3;
			red_count++;
			i += 2;
		}
		else
		{
			if (cmds->cmd == NULL)
			{
				cmds->cmd = mini->toks[i];
				i++;
			}
			else
			{
				cmds->args[0] = ft_strdup(cmds->cmd);
				while (mini->toks[i] && ft_strncmp(mini->toks[i], "|", 1) && !is_redirect(mini->toks[i]))
				{
					cmds->args[j] = mini->toks[i];
					j++;
					i++;
				}
				cmds->args[j] = NULL;
			}
		}
	}
	mini->cmds = head;
	return (1);
}
