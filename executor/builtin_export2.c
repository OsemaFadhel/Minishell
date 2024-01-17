/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:12:39 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/17 19:20:46 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_vars_sorted2(char **envp, int count)
{
	int	i;
	int	j;

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

void	ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	print_vars_sorted(char **envp)
{
	int		i;
	int		j;
	int		count;
	char	**tmp;
	char	*temp;

	tmp = env_dump(envp);
	count = ft_array_len(tmp);
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tmp[i], tmp[j]) > 0)
				ft_swap(&tmp[i], &tmp[j]);
			j++;
		}
		i++;
	}
	print_vars_sorted2(tmp, count);
	ft_free_array(tmp);
}

int	check_valid_identifier(char *arg)
{
	int	i;

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
