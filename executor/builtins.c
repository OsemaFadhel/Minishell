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

void is_builtin(t_mini *mini, t_cmds *current_cmd)
{
    if (strncmp(current_cmd->cmd, "echo", strlen("echo")) == 0)
        fd_echo(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "cd", strlen("cd")) == 0)
        fd_cd(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "pwd", strlen("pwd")) == 0)
        fd_pwd(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "export", strlen("export")) == 0)
        fd_export(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "unset", strlen("unset")) == 0)
        fd_unset(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "env", strlen("env")) == 0)
        fd_env(mini, current_cmd);
    else if (strncmp(current_cmd->cmd, "exit", strlen("exit")) == 0)
        fd_exit(mini, current_cmd);
    else
        return;
}