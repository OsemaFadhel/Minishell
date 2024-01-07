/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 20:42:49 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	is_redirect(char *str)
{
	if (str[0] == '>' || str[0] == '<')
		return (1);
	return (0);
}

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

int	count_args(t_mini *mini)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (mini->toks[i])
	{
		if (ft_strncmp(mini->toks[i], "|", 1) == 0)
			break ;
		else if (is_redirect(mini->toks[i]))
			i = count_red_arg(mini, i);
		else
		{
			while (mini->toks[i] && ft_strncmp(mini->toks[i], "|", 1) && !is_redirect(mini->toks[i]))
			{
				count++;
				i++;
			}
		}
	}
	return (count);
}

void	init_cmds(t_cmds *cmds, t_mini *mini)
{
	cmds->cmd = NULL;
	cmds->args = malloc(sizeof(char *) * (count_args(mini) + 1));
	cmds->redirect = malloc(sizeof(t_redirect) * 15);
	cmds->out = 0;
	cmds->in = 0;
	cmds->redirect_count = 0;
	cmds->next = NULL;
}

int	add_out_redirect(t_cmds *cmds, char **toks, int i, int type)
{
	if (!toks[i + 1] || ft_strncmp(toks[i + 1], "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (toks[i + 1][0] == '>' || toks[i + 1][0] == '<')
		i++;
	else
	{
		cmds->redirect[cmds->redirect_count].outfile = ft_strdup(toks[i + 1]);
		cmds->redirect[cmds->redirect_count].redirect_type = type;
		cmds->redirect_count++;
		cmds->out = 1;
		i += 2;
	}
	return (i);
}

int	add_in_redirect(t_cmds *cmds, char **toks, int	i, int type)
{
	if (!toks[i + 1] || ft_strncmp(toks[i + 1], "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (toks[i + 1][0] == '>' || toks[i + 1][0] == '<')
		i++;
	else
	{
		cmds->redirect[cmds->redirect_count].infile = ft_strdup(toks[i + 1]);
		cmds->redirect[cmds->redirect_count].redirect_type = type;
		cmds->redirect_count++;
		cmds->in = 1;
		i += 2;
	}
	return (i);
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
			i = add_out_redirect(cmds, mini->toks, i, 2);
			if (i == -1)
				return (0);
		}
		else if (!ft_strncmp(mini->toks[i], ">", 1))
		{
			i = add_out_redirect(cmds, mini->toks, i, 1);
			if (i == -1)
				return (0);
		}
		else if (!ft_strncmp(mini->toks[i], "<<", 2))
		{
			i = add_in_redirect(cmds, mini->toks, i, 4);
			if (i == -1)
				return (0);
		}
		else if (!ft_strncmp(mini->toks[i], "<", 1))
		{
			i = add_in_redirect(cmds, mini->toks, i, 3);
			if (i == -1)
				return (0);
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
