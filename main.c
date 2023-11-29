/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:18:50 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/29 16:03:30 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	mini->envp = malloc(sizeof(char *) * (i + 1));
	if (!mini->envp)
		return (1);
	i = 0;
	while (envp && envp[0] && envp[i])
	{
		mini->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->envp[i] = NULL;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_mini	mini;
	int		i;

	envdump(envp, &mini);

	while (1)
	{
		sig_ignore();
		input = readline("niggawhat$: ");

		add_history(input);
		if (lexersplit(input, &mini) == -1)
			return (1);

		/* exec try tests should start new process and do it*/

		if (mini.toks[0])
			executor(&mini);

		/* free cmds line so loop starts back clean */

		free_cmds(&mini, input);
	}
	return (0);
}
