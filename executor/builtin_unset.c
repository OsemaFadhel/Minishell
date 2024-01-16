/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/16 16:39:17 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
    i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_mini *mini __attribute((unused)), t_cmds *current_cmd)
{
	int	i;

	i = 1;
	while (current_cmd->args[i])
	{
		if (!is_valid_identifier(current_cmd->args[i]))
		{
			printf("BASH: unset: `%s': not a valid identifier\n", current_cmd->args[i]);
			g_exit_status = 1;
		}
		else
		{
			if (unsetenv(current_cmd->args[i]) != 0)
			{
				printf("BASH: unset: `%s': not found\n", current_cmd->args[i]);
				g_exit_status = 1;
			}
		}
		i++;
	}
	return (0);
}
