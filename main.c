/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/02 19:43:57 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_stack(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
}

void	free_cmds(t_mini *mini, char *input) // free cmds line
{
	int	i;

	i = 0;
	free(input);
	while (mini->toks[i])
	{
		free(mini->toks[i]);
		i++;
	}
	free(mini->toks);
	free_stack(mini->cmds);

}

int	envdump(char **envp, t_mini *mini) // get envp and put it in mini->envp
{
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
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
	mini->fdin = -2;
	mini->fdout = -2;
	mini->toks = NULL;
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
		//sig_ignore(&mini);
		add_history(input);
		if (lexersplit(input, &mini)) //creates matrix with all the words splitted and env changed
		{
			if (parser(&mini))
			{
				//printf("mini cmds  %s\n", mini.cmds->cmd);
				printf("if parser main\n");
					 /* exec try tests should start new process and do it*/
				execute(&mini);
			}
		}
		/* free cmds line so loop starts back clean */
		free_cmds(&mini, input);
	}
	return (0);
}
