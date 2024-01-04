/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/04 17:15:21 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

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

void	update_fd(t_mini *mini, t_cmds *current_cmd)
{
	int i;

	i = 0;
		while (current_cmd->redirect[i].redirect_type != 0)
		{
			if (current_cmd->redirect[i].redirect_type == 3) // <
			{
				mini->fdin = open(current_cmd->redirect[i].infile, O_RDONLY);
			}
			else if (current_cmd->redirect[i].redirect_type == 1) // >
		    {
		        mini->fdout = open(current_cmd->redirect[i].outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		    }
		    else if (current_cmd->redirect[i].redirect_type == 2) // >>
		    {
		        mini->fdout = open(current_cmd->redirect[i].outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		    }
			else if (current_cmd->redirect[i].redirect_type == 4) // <<
			{
				here_doc(mini, current_cmd->redirect[i].infile);
				mini->here_doc_flag = 1;

			}
			i++;
		}
}

void execute(t_mini *mini)
{
    // Save in/out
	int tmpin;
	int tmpout;
	int ret;
	int i;
	int cmd_count;
	t_cmds *current_cmd;

	// Set the initial input
	tmpin = dup(0);
	tmpout = dup(1);
	cmd_count = 0;
	current_cmd = mini->cmds;
	mini->fdin = dup(tmpin);
	while (current_cmd != NULL)
	{
		update_fd(mini, current_cmd);
		if (mini->fdin == -2 && cmd_count == 0)
			mini->fdin = dup(tmpin);
		dup2(mini->fdin, 0);
		close(mini->fdin);
		if	(mini->fdout == -2 || (current_cmd->next == NULL && current_cmd->redirect[0].redirect_type == 0))
			mini->fdout = dup(tmpout);
		if (mini->cmds_count >= 1)  // to check
		{
			int fdpipe[2]; // Create pipe
			pipe(fdpipe);
			mini->fdout = fdpipe[1];
			mini->fdin = fdpipe[0];
		}
		dup2(mini->fdout, 1);  // Redirect output
		close(mini->fdout);
		ret = fork();
		if (ret == 0)
		{
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

