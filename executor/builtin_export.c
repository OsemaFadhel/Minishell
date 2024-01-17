/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:56:34 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/17 18:50:43 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	print_vars_sorted2(char **envp, int count)
{
	int i;
	int j;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (envp[i][j] != '\0' && envp[i][j] != '=')
			ft_putchar_fd(envp[i][j++], 1);
		if (envp[i][j] == '=')
		{
			if (envp[i][j + 1] != '\0')
				ft_putstr_fd("=\"", 1);
			j++;
			while (envp[i][j] != '\0')
				ft_putchar_fd(envp[i][j++], 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**env_dump(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	print_vars_sorted(char **envp)
{
	int i;
	int j;
	int count;
	char **tmp;

	tmp = env_dump(envp);
	count = ft_array_len(tmp);
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tmp[i], tmp[j]) > 0)
			{
				char *temp = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_vars_sorted2(tmp, count);
	ft_free_array(tmp);
}

int	check_valid_identifier(char *arg)
{
	int i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		return (0);
	i++;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
		{
			if (arg[i + 1] && arg[i] == '+' && arg[i + 1] == '=')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_plus_equal(char *arg)
{
	int i;

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
	int i;
	char *name;

	i = 0;
	while (arg[i] != '+')
		i++;
	name = ft_substr(arg, 0, i);
	name = ft_strjoin(name, "=");
	return (name);
}

int	ft_export(t_mini *mini, t_cmds *current_cmd)
{
	int	i;
	char *name;
	char *value;
	char *tmp;

	i = 1;
	if (current_cmd->args[i] == NULL)
	{
		print_vars_sorted(mini->env);
		g_exit_status = 0;
		return (0);
	}
	while (current_cmd->args[i])
	{
		if (check_valid_identifier(current_cmd->args[i]) == 0)
		{
			printf("BASH: export: `%s': not a valid identifier\n", current_cmd->args[i]);
			g_exit_status = 1;
		}
		else if (check_plus_equal(current_cmd->args[i]))
		{
			name = get_name_plus(current_cmd->args[i]);
			tmp = get_env_var(name, mini->env);
			value = ft_strjoin(tmp, ft_substr(current_cmd->args[i], ft_strchr(current_cmd->args[i], '=') - current_cmd->args[i] + 1,
				ft_strlen(current_cmd->args[i])));
			ft_setenv(mini, name, value);
			free(name);
			free(tmp);
			free(value);
		}
		else if (ft_strchr(current_cmd->args[i], '='))
		{
			name = ft_substr(current_cmd->args[i], 0, ft_strchr(current_cmd->args[i], '=') - current_cmd->args[i] + 1);
			value = ft_substr(current_cmd->args[i], ft_strchr(current_cmd->args[i], '=') - current_cmd->args[i] + 1,
				ft_strlen(current_cmd->args[i]));
			ft_setenv(mini, name, value);
			free(name);
			free(value);
		}
		else
		{
			name = ft_strdup(current_cmd->args[i]);
			value = NULL;
			ft_setenv(mini, name, value);
			free(name);
		}
		i++;
	}
	return (0);
}
