/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:04:57 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:54 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	else_plus_equal(t_mini *mini, t_cmds *current_cmd, int i)
{
	char	*name;
	char	*value;
	char	*tmp;
	char	*tmp2;

	name = get_name_plus(current_cmd->args[i]);
	tmp = get_env_var(name, mini->env);
	tmp2 = ft_substr(current_cmd->args[i],
			ft_strchr(current_cmd->args[i], '=')
			- current_cmd->args[i] + 1,
			ft_strlen(current_cmd->args[i]));
	value = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	ft_setenv(mini, name, value);
	free(name);
	free(value);
}

void	last_elseif(t_mini *mini, t_cmds *current_cmd, int i)
{
	char	*name;
	char	*value;

	name = ft_substr(current_cmd->args[i], 0,
			ft_strchr(current_cmd->args[i], '=')
			- current_cmd->args[i] + 1);
	value = ft_substr(current_cmd->args[i],
			ft_strchr(current_cmd->args[i], '=')
			- current_cmd->args[i] + 1,
			ft_strlen(current_cmd->args[i]));
	ft_setenv(mini, name, value);
	free(name);
	free(value);
}

void	last_else(t_mini *mini, t_cmds *current_cmd, int i)
{
	char	*name;
	char	*value;

	name = ft_strdup(current_cmd->args[i]);
	value = NULL;
	ft_setenv(mini, name, value);
	free(name);
}
