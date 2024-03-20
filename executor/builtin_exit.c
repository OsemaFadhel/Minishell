/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:06:10 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:53 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static long	str_to_int(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result * sign);
}

int	handle_exit_args(t_mini *mini, t_cmds *current_cmd)
{
	char	*endptr;
	long	exit_status;

	if (current_cmd->args[1] != NULL)
	{
		exit_status = str_to_int(current_cmd->args[1]);
		if (exit_status == -1)
		{
			printf("exit: %s: numeric argument required\n",
				current_cmd->args[1]);
			g_exit_status = 255;
			return (0);
		}
		if (current_cmd->args[2] != NULL)
		{
			ft_putstr_fd("BASH: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return (1);
		}
		g_exit_status = (exit_status % 256 + 256) % 256;
	}
	return (0);
}

int	ft_exit(t_mini *mini, t_cmds *current_cmd)
{
	(void)current_cmd;
	if (handle_exit_args(mini, current_cmd) == 1)
		return (0);
	free_cmds(&*mini);
	ft_free_array(mini->env);
	exit(g_exit_status);
}
