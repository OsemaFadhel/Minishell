/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/21 15:35:41 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
	mini->input = NULL;
	mini->output = NULL;
	mini->history = NULL;
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
		//sig_ignore();
		input = readline("niggawhat$: ");

		add_history(input);
		if (lexersplit(input, &mini) == -1) //creates matrix with all the words splitted and env changed
			return (1);

		/*if (parser(&mini, &mini.cmds) == -1) //creates linked list with all the commands and its info
			return (1);*/

		if (mini.toks[0]) /* exec try tests should start new process and do it*/
			executor(&mini);

		/* free cmds line so loop starts back clean */
		free_cmds(&mini, input);
	}
	return (0);
}
