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
#include "../include/builtins.h"

static const struct builtins_s_list	builtins_g_builtins[] = {
	{"echo", builtins_echo},
	{"cd", builtins_cd},
	{"pwd", builtins_pwd},
	{"env", builtins_env},
	{"export", builtins_export},
	{"unset", builtins_unset},
	{"exit", builtins_exit},
	{NULL, NULL},
};

int split_count(char **array)
{
    int i = 0;

    while (array[i] != NULL)
        i++;

    return i;
}

int	builtin_check(char **argv)
{
	int	c_name;
	int	i;

	i = 0;
	if (argv[0] && !strncmp(argv[0], "exit", 5))
		return (INT_MAX);
	while (builtins_g_builtins[i].name != NULL && argv)
	{
		c_name = strlen(builtins_g_builtins[i].name);
		if (argv[0] && !strncmp(argv[0], builtins_g_builtins[i].name, c_name + 1))
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtins_exec(char **argv, bool subshell, t_list *l_free)
{
	int	i_builtin;

	i_builtin = builtin_check(argv);
	if (i_builtin == 0)
		return (ERROR);
	errno = 0;
	if (i_builtin == INT_MAX)
		return (builtin_exit(split_count(argv), argv, subshell, l_free));
	return (builtins_g_builtins[i_builtin - 1].func(split_count(argv), argv));
}
















/*
int is_builtin(t_mini *mini, t_cmds *cmds, int i)
{
    if (!builtin(mini, cmds, i) || !builtin_2(mini, cmds, i) || !builtin_3(mini, cmds, i))
        return (0);
    return (1);
}
*/

/*

questo file main contiene il ciclo che chiama la funzione della singola builtin in caso di match
usando strncmp per confrontare la stringa con la prima parola dell'array di args e se corrisponde
ad una delle builtin la esegue e ritorna 0, altrimenti ritorna 1 e il ciclo continua.

*/

/*
int builtin(t_mini *mini, t_cmds *cmds, int i)
{
    if (strncmp(cmds->args[0], "exit", 4) == 0)
        exit(0);
    else if (strncmp(cmds->args[0], "echo", 4) == 0 && cmds->args[1])
    {
        i = 1;
        if (strncmp(cmds->args[i], "-n", 2) == 0)
        {
            i++;
            while (cmds->args[i])
            {
                ft_putstr_fd(cmds->args[i], 1);
                i++;
                if (cmds->args[i])
                    write(1, " ", 1);
            }
        }
        else
        {
            while (cmds->args[i])
            {
                ft_putstr_fd(cmds->args[i], 1);
                if (cmds->args[i + 1])
                    write(1, " ", 1);
                i++;
            }
            write(1, "\n", 1);
        }
        return (0);
    }
    return (1);
}

int builtin_2(t_mini *mini, t_cmds *cmds, int i)
{
    if (strncmp(cmds->args[0], "env", 3) == 0)
    {
        while (mini->env[i])
        {
            printf("%s\n", mini->env[i]);
            i++;
        }
        printf("\n");
    }
    else if (strncmp(cmds->args[0], "unset", 5) == 0)
    {
        if (cmds->args[1] == NULL)
            return (0);
        while (cmds->args[i])
        {
            if (ft_isdigitalpha(cmds->args[i]) == 0)
            {
                write(1, "unset: not a valid identifier\n", 31);
                return (0);
            }
            i++;
        }
        mini->env = unset_cmd(mini->env, cmds->args[1]);
    }
    else
        return (1);
    return (0);
}

int builtin_3(t_mini *mini, t_cmds *cmds, int i)
{
    if (strncmp(cmds->args[0], "cd", 2) == 0)
    {
        if (cmds->args[1])
            chdir(cmds->args[1]);
        else
            chdir(getenv("HOME"));
    }
    else if (strncmp(cmds->args[0], "pwd", 3) == 0)
        printf("%s\n", getcwd(NULL, 0));
    else
        return (1);
    return (0);
}

*/