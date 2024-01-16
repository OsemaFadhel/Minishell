/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/16 17:15:07 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export(t_mini *mini, t_cmds *current_cmd)
{
	return (0);
}

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
