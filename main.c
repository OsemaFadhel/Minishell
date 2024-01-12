/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/12 18:17:46 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_exit_status = 0;

int	envdump(char **envp, t_mini *mini) // get envp and put it in mini->envp
{
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	mini->env = ft_calloc(sizeof(char *), (i + 1));
	if (!mini->env)
		return (1);
	i = 0;
	while (envp && envp[0] && envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->env[i] = NULL;
	return (0);
}

void	init(t_mini *mini)
{
	mini->cmds = NULL;
	mini->cmds_count = 0;
	mini->here_doc_flag = 0;
	mini->toks = NULL;
	mini->fdin = 0;
	mini->fdout = 0;
	mini->toks_count = 0;
	sig_ignore();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_mini	mini;
	int		i;

	envdump(envp, &mini);
	while (1)
	{
		init(&mini);
		input = readline("BASH$: ");
		if (input && input[0])
			add_history(input);
		if (input == NULL)
			ft_ctrld(input, &mini);
		if (input && input[0])
		{
			if (lexersplit(input, &mini) != -1)
			{
				if (parser(&mini))
					execute(&mini);
				free_cmds(&mini);
			}
		}
	}
	return (0);
}
