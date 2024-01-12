/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:24:13 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/12 16:56:07 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_doc(t_mini *mini, char *delimeter)
{
	char	*line;
	int		fd;

	fd = open("tmp.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	mini->fdin = open("tmp.txt", O_RDONLY);
}

void	in_redirect2(t_mini *mini, t_cmds *current_cmd, int i)
{
	if (mini->here_doc_flag == 0)
	{
		if (mini->fdin > 0)
			close(mini->fdin);
		here_doc(mini, current_cmd->redirect[i].infile);
		mini->here_doc_flag = 1;
	}
	else
	{
		if (mini->fdin > 0)
			close(mini->fdin);
		here_doc(mini, current_cmd->redirect[i].infile);
	}
}

int	in_redirect(t_mini *mini, t_cmds *current_cmd)
{
	int	i;

	i = 0;
	mini->here_doc_flag = 0;
	while (current_cmd->redirect[i].redirect_type != 0)
	{
		if (current_cmd->redirect[i].redirect_type == 3)
		{
			if (mini->fdin != 0)
				close(mini->fdin);
			mini->fdin = open(current_cmd->redirect[i].infile, O_RDONLY);
			if (mini->fdin == -1)
			{
				return (perror("BASH$:"), -1);
				g_exit_status = 1;
			}
		}
		else if (current_cmd->redirect[i].redirect_type == 4)
			in_redirect2(mini, current_cmd, i);
		i++;
	}
	return (0);
}

void	out_redirect2(t_mini *mini, t_cmds *current_cmd, int i)
{
	if (mini->fdout != 1)
		close(mini->fdout);
	mini->fdout = open(current_cmd->redirect[i].outfile,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
}

void	out_redirect(t_mini *mini, t_cmds *current_cmd)
{
	int	i;

	i = 0;
	while (current_cmd->redirect[i].redirect_type != 0)
	{
		if (current_cmd->redirect[i].redirect_type == 1)
		{
			if (mini->fdout != 1)
				close(mini->fdout);
			mini->fdout = open(current_cmd->redirect[i].outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (current_cmd->redirect[i].redirect_type == 2)
			out_redirect2(mini, current_cmd, i);
		i++;
	}
}
