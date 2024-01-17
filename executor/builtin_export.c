/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:56:34 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/17 19:35:56 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_plus_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+')
		{
			if (arg[i + 1] && arg[i + 1] == '=')
				return (1);
		}
		i++;
	}
	return (0);
}

char	*get_name_plus(char *arg)
{
	int		i;
	char	*name;
	char	*tmp;

	i = 0;
	while (arg[i] != '+')
		i++;
	tmp = ft_substr(arg, 0, i);
	name = ft_strjoin(tmp, "=");
	free(tmp);
	return (name);
}

int	print_export(t_mini *mini, t_cmds *current_cmd)
{
	if (current_cmd->args[1] == NULL)
	{
		print_vars_sorted(mini->env);
		g_exit_status = 0;
		return (0);
	}
	return (1);
}

int	ft_export(t_mini *mini, t_cmds *current_cmd)
{
	int		i;

	i = 1;
	if (print_export(mini, current_cmd) == 0)
		return (0);
	while (current_cmd->args[i])
	{
		if (check_valid_identifier(current_cmd->args[i]) == 0)
		{
			printf("BASH: export: `%s': not a valid identifier\n",
				current_cmd->args[i]);
			g_exit_status = 1;
			return (1);
		}
		else if (check_plus_equal(current_cmd->args[i]))
			else_plus_equal(mini, current_cmd, i);
		else if (ft_strchr(current_cmd->args[i], '='))
			last_elseif(mini, current_cmd, i);
		else
			last_else(mini, current_cmd, i);
		i++;
	}
	g_exit_status = 0;
	return (0);
}
