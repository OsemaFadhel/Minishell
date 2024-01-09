/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:24:13 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 12:34:24 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

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

void	in_redirect(t_mini *mini, t_cmds *current_cmd)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	while (current_cmd->redirect[i].redirect_type != 0)
	{
		if (current_cmd->redirect[i].redirect_type == 3) // <
		{
			if (flag == 0)
			{
				mini->fdin = open(current_cmd->redirect[i].infile, O_RDONLY);
				flag = 1;
			}
			else
			{
				if (mini->fdin > 0)
					close(mini->fdin);
				mini->fdin = open(current_cmd->redirect[i].infile, O_RDONLY);
			}
		}
		else if (current_cmd->redirect[i].redirect_type == 4) // <<
		{
			if (flag == 0)
			{
				here_doc(mini, current_cmd->redirect[i].infile);
				flag = 1;
			}
			else
			{
				if (mini->fdin > 0)
					close(mini->fdin);
				here_doc(mini, current_cmd->redirect[i].infile);
			}
			mini->here_doc_flag = 1;
		}
		i++;
	}
}

void	out_redirect(t_mini *mini, t_cmds *current_cmd)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	while (current_cmd->redirect[i].redirect_type != 0)
	{
		if (current_cmd->redirect[i].redirect_type == 1) // >
		{
			if (flag == 0)
			{
				mini->fdout = open(current_cmd->redirect[i].outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
				flag = 1;
			}
			else
			{
				if (mini->fdout > 0)
					close(mini->fdout);
				mini->fdout = open(current_cmd->redirect[i].outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			}
		}
		else if (current_cmd->redirect[i].redirect_type == 2) // >>
		{
			if (flag == 0)
			{
				mini->fdout = open(current_cmd->redirect[i].outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
				flag = 1;
			}
			else
			{
				if (mini->fdout > 0)
					close(mini->fdout);
				mini->fdout = open(current_cmd->redirect[i].outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
			}
		}
		i++;
	}
}

void	update_fd(t_mini *mini, t_cmds *current_cmd)
{
	if (current_cmd->in == 1)
	{
		close(mini->fdin);
		in_redirect(mini, current_cmd);
		if (mini->fdin > 0)
			dup2(mini->fdin, 0);
		if (mini->fdin > 0)
			close(mini->fdin);
	}
	if (current_cmd->out == 1)
	{
		close(mini->fdout);
		out_redirect(mini, current_cmd);
	}
	printf("fdout = %d\n", mini->fdout);
	if (mini->fdout > 0)
		dup2(mini->fdout, 1);
	if (mini->fdout > 0)
		close(mini->fdout);
}
