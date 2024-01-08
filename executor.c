/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/08 18:14:23 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
	if (mini->fdout > 0)
		dup2(mini->fdout, 1);
	if (mini->fdout > 0)
		close(mini->fdout);
}

void execute(t_mini *mini)
{
    // Save in/out
	int tmpin;
	int tmpout;
	int ret;
	int i;
	int cmd_count;
	int	pipe_flag;
	t_cmds *current_cmd;

	// Set the initial input
	tmpin = dup(0);
	tmpout = dup(1);
	cmd_count = 0;
	current_cmd = mini->cmds;
	mini->fdin = dup(tmpin);
	while (current_cmd != NULL)  //missing case like like ls >file txt | wc -l //the fdin for wc need to be the fdout of ls
	{
		// check in red
		dup2(mini->fdin, 0);
		close(mini->fdin);
		if	(current_cmd->out == 0 || (current_cmd->next == NULL && current_cmd->out == 0))
			mini->fdout = dup(tmpout);
		if (mini->cmds_count >= 1 /*&& current_cmd->out == 0 */&& current_cmd->next != NULL)  // to check
		{
			int fdpipe[2]; // Create pipe
			pipe(fdpipe);
			mini->fdout = fdpipe[1];
			mini->fdin = fdpipe[0];
			pipe_flag = 1;
		}
		else
			pipe_flag = 0;
		update_fd(mini, current_cmd);
		ret = fork();
		if (ret == 0)
		{
			close(mini->fdin);
			close(tmpin);
			close(tmpout);
			executor(mini, current_cmd); // Call the executor with the current command
			exit(1);
		}
		current_cmd = current_cmd->next;
		cmd_count++;
		if (mini->here_doc_flag == 1)
			unlink("tmp.txt");
	}
	// Restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	while (waitpid(-1, NULL, 0) > 0);
}
