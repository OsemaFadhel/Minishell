/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/16 18:33:34 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_var(t_mini *mini, const char *var)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var, ft_strlen(var)) == 0
			&& mini->env[i][ft_strlen(var)] == '=')
		{
			free(mini->env[i]);
			while (mini->env[i])
			{
				mini->env[i] = mini->env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

int	ft_unset(t_mini *mini, t_cmds *current_cmd)
{
	int	i;

	i = 1;
	while (current_cmd->args[i])
	{
		if (!is_valid_identifier(current_cmd->args[i]))
		{
			printf("BASH: unset: `%s': not a valid identifier\n",
				current_cmd->args[i]);
			g_exit_status = 1;
		}
		else
		{
			remove_env_var(mini, current_cmd->args[i]);
		}
		i++;
	}
	return (0);
}
