/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_fds2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:05:38 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:57 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	update_fd(t_mini *mini, t_cmds *current_cmd, int tmpout)
{
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

void	store_std(int *tmpin, int *tmpout)
{
	*tmpin = dup(0);
	*tmpout = dup(1);
}
