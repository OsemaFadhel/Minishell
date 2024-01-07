/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 21:43:57 by ofadhel          ###   ########.fr       */
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

int	count_redirect(t_mini *mini, t_parser *parser)
{
	int count;

	count = 0;
	while (mini->toks[parser->k] && ft_strncmp(mini->toks[parser->k], "|", 1))
	{
		printf("mini->toks[parser->k]: %s\n", mini->toks[parser->k]);
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

void	init_cmds(t_cmds *cmds, t_mini *mini, t_parser *parser)
{
	cmds->cmd = NULL;
	cmds->args = malloc(sizeof(char *) * (count_args(mini) + 1));
	cmds->redirect = malloc(sizeof(t_redirect) * (count_redirect(mini, parser) + 1));
	cmds->out = 0;
	cmds->in = 0;
	cmds->redirect_count = 0;
	cmds->next = NULL;
}

int	add_out_redirect(t_cmds *cmds, char **toks, t_parser *parser, int type)
{
	if (!toks[parser->i + 1] || ft_strncmp(toks[parser->i + 1], "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (toks[parser->i + 1][0] == '>' || toks[parser->i + 1][0] == '<')
		parser->i++;
	else
	{
		cmds->redirect[cmds->redirect_count].outfile = ft_strdup(toks[parser->i + 1]);
		cmds->redirect[cmds->redirect_count].redirect_type = type;
		cmds->redirect_count++;
		cmds->out = 1;
		parser->i += 2;
	}
	return (parser->i);
}

int	add_in_redirect(t_cmds *cmds, char **toks, t_parser *parser , int type)
{
	if (!toks[parser->i + 1] || ft_strncmp(toks[parser->i + 1], "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (toks[parser->i + 1][0] == '>' || toks[parser->i + 1][0] == '<')
		parser->i++;
	else
	{
		cmds->redirect[cmds->redirect_count].infile = ft_strdup(toks[parser->i + 1]);
		cmds->redirect[cmds->redirect_count].redirect_type = type;
		cmds->redirect_count++;
		cmds->in = 1;
		parser->i += 2;
	}
	return (parser->i);
}

int	parser(t_mini *mini)
{
	t_parser parser;
	t_cmds	*cmds;
	t_cmds  *head;

	parser.i = 0;
	parser.j = 1;
	parser.k = 0;
	head = cmds = malloc(sizeof(t_cmds));
	init_cmds(cmds, mini, &parser);
	while (mini->toks[parser.i])
	{
		if (ft_strncmp(mini->toks[parser.i], "|", 1) == 0)
		{
			mini->cmds_count++;
			cmds->next = malloc(sizeof(t_cmds));
			cmds = cmds->next;
			parser.k++;
			init_cmds(cmds, mini, &parser);
			parser.i++;
			parser.j = 1;
		}
		else if (!ft_strncmp(mini->toks[parser.i], ">>", 2))
		{
			if (add_out_redirect(cmds, mini->toks, &parser, 2) == -1)
				return (0);
		}
		else if (!ft_strncmp(mini->toks[parser.i], ">", 1))
		{
			if (add_out_redirect(cmds, mini->toks, &parser, 1) == -1)
				return (0);
		}
		else if (!ft_strncmp(mini->toks[parser.i], "<<", 2))
		{
			if (add_in_redirect(cmds, mini->toks, &parser, 4) == -1)
				return (0);
		}
		else if (!ft_strncmp(mini->toks[parser.i], "<", 1))
		{
			if (add_in_redirect(cmds, mini->toks, &parser, 3) == -1)
				return (0);
		}
		else
		{
			if (cmds->cmd == NULL)
			{
				cmds->cmd = ft_strdup(mini->toks[parser.i]);
				cmds->args[0] = ft_strdup(mini->toks[parser.i]);
				parser.i++;
			}
			else
			{
				while (mini->toks[parser.i] && ft_strncmp(mini->toks[parser.i], "|", 1)
					&& !is_redirect(mini->toks[parser.i]))
				{
					cmds->args[parser.j] = ft_strdup(mini->toks[parser.i]);
					parser.j++;
					parser.i++;
				}
				cmds->args[parser.j] = NULL;
			}
		}
	}
	mini->cmds = head;
	return (1);
}
