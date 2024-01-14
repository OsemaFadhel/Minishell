/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/14 16:19:47 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process(t_mini *mini, t_cmds *current_cmd, int tmpin, int tmpout)
{
	if (update_fd(mini, current_cmd, tmpout) == -1)
		return (-1);
	if (ft_fork(mini, current_cmd, tmpin, tmpout) == -1)
	{
		restore_stds(tmpin, tmpout);
		return (-1);
	}
	return (0);
}

void	first_part(t_mini *mini, t_cmds	*current_cmd, int cmd_count, int tmpout)
{
	dup2(mini->fdin, 0);
	close(mini->fdin);
	set_pipes(mini, current_cmd, cmd_count, tmpout);
}

void	execute(t_mini *mini)
{
	int		tmpin;
	int		tmpout;
	int		cmd_count;
	t_cmds	*current_cmd;
	int		status;

	store_std(&tmpin, &tmpout);
	cmd_count = 0;
	current_cmd = mini->cmds;
	mini->fdin = dup(tmpin);
	while (current_cmd != NULL)
	{
		first_part(mini, current_cmd, cmd_count, tmpout);
		if (process(mini, current_cmd, tmpin, tmpout) == -1)
			return ;
		current_cmd = current_cmd->next;
		cmd_count++;
		if (mini->here_doc_flag == 1)
			unlink("tmp.txt");
	}
	restore_stds(tmpin, tmpout);
	if (mini->exec_flag == 1)
	{
		while (waitpid(-1, &status, 0) > 0)
			;
		g_exit_status = WEXITSTATUS(status);
	}
}
