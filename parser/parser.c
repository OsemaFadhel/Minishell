/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 01:51:16 by ofadhel          ###   ########.fr       */
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

int	count_red(char **toks)
{
	static int i;
	int count;

	i = 0;
	count = 0;
	while (toks[i] && ft_strncmp(toks[i], "|", 1))
	{
		if (!ft_strncmp(toks[i], ">>", 2) || !ft_strncmp(toks[i], ">", 1) || !ft_strncmp(toks[i], "<<", 2) || !ft_strncmp(toks[i], "<", 1))
			count++;
		i++;
	}
	return (count);
}

void	init_cmds(t_cmds *cmds, t_mini *mini)
{
	cmds->cmd = NULL;
	cmds->args = malloc(sizeof(char *) * 120);
	cmds->redirect = malloc(sizeof(t_redirect) * 15);
	cmds->out = 0;
	cmds->in = 0;
	cmds->fdin = 0;
	cmds->fdout = 0;
	cmds->redirect_count = 0;
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
	t_cmds	*cmds;
	t_cmds  *head;

	i = 0;
	j = 1;
	head = cmds = malloc(sizeof(t_cmds));
	init_cmds(cmds, mini);
	while (mini->toks[i])
	{
		if (ft_strncmp(mini->toks[i], "|", 1) == 0)
		{
			mini->cmds_count++;
			cmds->next = malloc(sizeof(t_cmds));
			cmds = cmds->next;
			init_cmds(cmds, mini);
			i++;
		}
		else if (!ft_strncmp(mini->toks[i], ">>", 2))
		{
			init_redirect(&cmds->redirect[cmds->redirect_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1] == "|")
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[cmds->redirect_count].outfile = ft_strdup(mini->toks[i + 1]);;
			cmds->redirect[cmds->redirect_count].redirect_type = 2;
			cmds->redirect_count++;
			cmds->out = 1;
			i += 2;
		}
		else if (!ft_strncmp(mini->toks[i], ">", 1))
		{
			init_redirect(&cmds->redirect[cmds->redirect_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1] == "|")
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[cmds->redirect_count].outfile = ft_strdup(mini->toks[i + 1]);;
			cmds->redirect[cmds->redirect_count].redirect_type = 1;
			cmds->redirect_count++;
			cmds->out = 1;
			i += 2;
		}
		else if (!ft_strncmp(mini->toks[i], "<<", 2))
		{
			init_redirect(&cmds->redirect[cmds->redirect_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1] == "|")
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[cmds->redirect_count].infile = ft_strdup(mini->toks[i + 1]);;
			cmds->redirect[cmds->redirect_count].redirect_type = 4;
			cmds->redirect_count++;
			cmds->in = 1;
			i += 2;
		}
		else if (!ft_strncmp(mini->toks[i], "<", 1))
		{
			init_redirect(&cmds->redirect[cmds->redirect_count]);
			if (!mini->toks[i + 1] || mini->toks[i + 1][0] == '|')
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			cmds->redirect[cmds->redirect_count].infile = ft_strdup(mini->toks[i + 1]);
			cmds->redirect[cmds->redirect_count].redirect_type = 3;
			cmds->redirect_count++;
			cmds->in = 1;
			i += 2;
		}
		else
		{
			if (cmds->cmd == NULL)
			{
				cmds->cmd = ft_strdup(mini->toks[i]);
				cmds->args[0] = ft_strdup(mini->toks[i]);
				i++;
			}
			else
			{
				while (mini->toks[i] && ft_strncmp(mini->toks[i], "|", 1) && !is_redirect(mini->toks[i]))
				{
					cmds->args[j] = ft_strdup(mini->toks[i]);
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
