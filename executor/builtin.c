/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:05:23 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:55 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_mini *mini, t_cmds *current_cmd)
{
	if (ft_strncmp(current_cmd->cmd, "echo", 5) == 0)
		ft_echo(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "cd", 3) == 0)
		ft_cd(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "exit", 5) == 0)
		ft_exit(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "pwd", 4) == 0)
		ft_pwd(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "env", 4) == 0)
		ft_env(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "export", 7) == 0)
		ft_export(mini, current_cmd);
	else if (ft_strncmp(current_cmd->cmd, "unset", 6) == 0)
		ft_unset(mini, current_cmd);
	else
		return (0);
	return (1);
}
