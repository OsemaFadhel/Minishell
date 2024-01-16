/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:43:57 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/16 15:44:20 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(t_mini *mini __attribute((unused)), t_cmds *current_cmd) //completed
{
	int		i;
	int		newline;

	newline = 0;
	i = 1;
	while (current_cmd->args[i] && !ft_strncmp(current_cmd->args[i], "-n", 3))
		i++;
	if (i == 1)
		newline = 1;
	while (current_cmd->args[i])
	{
		ft_putstr_fd(current_cmd->args[i], 1);
		if (current_cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
	return (0);
}

int	ft_pwd(t_mini *mini, t_cmds *current_cmd) //completed
{
	char	*path;

	(void)current_cmd;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	g_exit_status = 0;
	return (0);
}

int	ft_env(t_mini *mini, t_cmds *current_cmd) //completed
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)current_cmd;
	while (mini->env[i])
	{
		j = 0;
		while (mini->env[i][j])
		{
			if (mini->env[i][j] == '=')
			{
				printf("%s\n", mini->env[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	g_exit_status = 0;
	return (0);
}
