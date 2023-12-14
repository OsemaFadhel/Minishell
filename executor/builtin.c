/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/14 12:53:36 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	is_builtin(t_mini *mini, int i) //check if the command is a builtin
{
	if (!builtin(mini, i) || !builtin_2(mini, i) || !builtin_3(mini, i))
		return (0);
	return (1);
}

int	builtin(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "exit") == 0) //free everything and exit
			exit(0);
	/*else if (strcmp(mini->toks[0], "echo") == 0 && mini->toks[1])
	{
		i = 1;
		if (strncmp(mini->toks[i], "-n", 2) == 0) //funzione che trova la prima parola e fa strcmp con -n
		{
			i++;
			while (mini->toks[i])
			{
				ft_putstr_fd(mini->toks[i], 1); // ricordarsi nel parser di cambiare il $ con il valore della variabile d'ambiente
				i++;
				//if (mini->toks[i])
				//	write(1, " ", 1);
			}
		}
		else
		{
			while (mini->toks[i])
			{
				ft_putstr_fd(mini->toks[i], 1);
				//write(1, " ", 1);
				i++;
			}
			printf("\n");
		}
		return (0);
	}*/
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
	/*else if (strcmp(mini->toks[0], "export") == 0);*/
	else if (strcmp(mini->toks[0], "unset") == 0)
	{
		//funzione che cerca la variabile d'ambiente e la elimina
		if (mini->toks[1] == NULL)
			return (0);
		while (mini->toks[i])
		{
			if (ft_isdigitalpha(mini->toks[i]) == 0)
			{
				write(1, "unset: not a valid identifier\n", 31);
				return (0);
			}
			i++;
		}
		mini->envp = unset_cmd(mini->envp, mini->toks[1]);
	}
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