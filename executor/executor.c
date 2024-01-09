/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 19:50:19 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fork(t_mini *mini, t_cmds *current_cmd, int tmpin, int tmpout)
{
	pid_t ret;

	ret = fork();
	if (ret == 0)
	{
		close(mini->fdin);
		close(tmpin);
		close(tmpout);
		executor(mini, current_cmd); // Call the executor with the current command
		exit(0);
	}
}

void	restore_stds(int tmpin, int tmpout, t_mini *mini)
{
	/*close(mini->fdpipe[0]);
	close(mini->fdpipe[1]);*/
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void	set_pipes(t_mini *mini, t_cmds *current_cmd, int cmd_count, int tmpout)
{
	if	(current_cmd->out == 0 || (current_cmd->next == NULL && current_cmd->out == 0))
		mini->fdout = dup(tmpout);
	if (mini->cmds_count >= 1 && current_cmd->next != NULL)  // to check
	{
		pipe(mini->fdpipe);
		mini->fdout = mini->fdpipe[1];
		mini->fdin = mini->fdpipe[0];
	}
}

void execute(t_mini *mini)
{
	int tmpin;
	int tmpout;
	int i;
	int cmd_count;
	t_cmds *current_cmd;

	tmpin = dup(0);
	tmpout = dup(1);
	cmd_count = 0;
	current_cmd = mini->cmds;
	mini->fdin = dup(tmpin);
	while (current_cmd != NULL)  //missing case like like ls >file txt | wc -l //the fdin for wc need to be the fdout of ls
	{
		dup2(mini->fdin, 0);
		close(mini->fdin);
		set_pipes(mini, current_cmd, cmd_count, tmpout);
		update_fd(mini, current_cmd);
		ft_fork(mini, current_cmd, tmpin, tmpout);
		current_cmd = current_cmd->next;
		cmd_count++;
		if (mini->here_doc_flag == 1)
			unlink("tmp.txt");
	}
	restore_stds(tmpin, tmpout, mini);
	while (waitpid(-1, NULL, 0) > 0);
}
