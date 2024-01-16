/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/10 23:26:43 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void is_builtin(t_mini *mini, t_cmds *current_cmd, int i)
{
    i = 0;
    if (strncmp(current_cmd->cmd, "echo", strlen("echo")) == 0)
            ft_echo(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "cd", strlen("cd")) == 0)
        ft_cd(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "exit", strlen("exit")) == 0)
        ft_exit(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "pwd", strlen("pwd")) == 0)
        ft_pwd(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "unset", strlen("unset")) == 0)
        ft_unset(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "env", strlen("env")) == 0)
        ft_env(mini, current_cmd);
    else
        return;
}