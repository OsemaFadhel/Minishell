/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/12 17:43:47 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fork(t_mini *mini, t_cmds *current_cmd, int tmpin, int tmpout)
{
	pid_t	ret;

	ret = fork();
	if (ret == 0)
	{
		close(mini->fdin);
		close(tmpin);
		close(tmpout);
		executor(mini, current_cmd);
		free_cmds(mini);
		exit(127);
	}
	return (0);
}

void	restore_stds(int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void	set_pipes(t_mini *mini, t_cmds *current_cmd, int cmd_count, int tmpout)
{
	int	fdpipe[2];

	if (current_cmd->out == 0
		|| (current_cmd->next == NULL && current_cmd->out == 0))
		mini->fdout = dup(tmpout);
	if (mini->cmds_count >= 1 && current_cmd->next != NULL)
	{
		pipe(fdpipe);
		mini->fdout = fdpipe[1];
		mini->fdin = fdpipe[0];
	}
}

int	update_fd(t_mini *mini, t_cmds *current_cmd, int cmd_count, int tmpout)
{
	set_pipes(mini, current_cmd, cmd_count, tmpout);
	if (current_cmd->in == 1)
	{
		close(mini->fdin);
		if (in_redirect(mini, current_cmd) == -1)
			return (-1);
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
	dup2(mini->fdout, 1);
	close(mini->fdout);
	return (0);
}

void	execute(t_mini *mini)
{
	int		tmpin;
	int		tmpout;
	int		cmd_count;
	t_cmds	*current_cmd;
	int		status;

	tmpin = dup(0);
	tmpout = dup(1);
	cmd_count = 0;
	current_cmd = mini->cmds;
	mini->fdin = dup(tmpin);
	while (current_cmd != NULL)
	{
		dup2(mini->fdin, 0);
		close(mini->fdin);
		if (update_fd(mini, current_cmd, cmd_count, tmpout) == -1)
			return ;
		if (ft_fork(mini, current_cmd, tmpin, tmpout) == -1)
		{
			restore_stds(tmpin, tmpout);
			return ;
		}
		current_cmd = current_cmd->next;
		cmd_count++;
		if (mini->here_doc_flag == 1)
			unlink("tmp.txt");
	}
	restore_stds(tmpin, tmpout);
	while (waitpid(-1, &status, 0) > 0)
		;
	g_exit_status = WEXITSTATUS(status);
}
