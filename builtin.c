/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/24 21:45:12 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	is_builtin(t_mini *mini, int i)
{
	if (!builtin(mini, i) || !builtin_2(mini, i) || !builtin_3(mini, i))
		return (0);
	return (1);
}

int	builtin(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "exit") == 0)
			exit(0);
	else if (strcmp(mini->toks[0], "echo") == 0 && mini->toks[1]) // fare che la prima parola dell'arg sia -n e se si allora non mettere \n
	{
		i = 1;
		if (strncmp(mini->toks[1], "-n", 2) == 0) //funzione che trova la prima parola e fa strcmp con -n
		{
			while (mini->toks[i])
			{
				printf("%s ", mini->toks[i]); // ricordarsi nel parser di cambiare il $ con il valore della variabile d'ambiente
				i++;
			}
		}
		else
		{
			while (mini->toks[i])
			{
				printf("%s ", mini->toks[i]);
				i++;
			}
			printf("\n");
		}
		return (0);
	}
	return (1);
}

int	builtin_2(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "env") == 0)
	{
		while (mini->envp[i])
		{
			printf("%s\n", mini->envp[i]);
			i++;
		}
		printf("\n");
	}
	/*else if (strcmp(mini->toks[0], "export") == 0);
	else if (strcmp(mini->toks[0], "unset") == 0)*/
	else
		return (1);
	return (0);
}

int	builtin_3(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "cd") == 0)
	{
		if (mini->toks[1])
			chdir(mini->toks[1]);
		else
			chdir(getenv("HOME"));
		//change_pwd(mini);
		//cambiare la variabile d'ambiente PWD nell'envp
	}
	else if	(strcmp(mini->toks[0], "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0)); // questo oppure cerca nell'envp la variabile PWD e la printa
	else
		return (1);
	return (0);
}
