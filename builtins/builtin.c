/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:51:47 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/31 21:27:16 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

/*int	is_builtin(t_mini *mini, t_cmds *cmds, int i) //check if the command is a builtin
{
	if (!builtin(mini, i) || !builtin_2(mini, i) || !builtin_3(mini, i))
		return (0);
	return (1);
}

int	builtin(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "exit") == 0) //free everything and exit
			exit(0);
	else if (strcmp(mini->toks[0], "echo") == 0 && mini->toks[1])
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
	}
	return (1);
}

int	builtin_2(t_mini *mini, int i)
{
	if (strcmp(mini->toks[0], "env") == 0)
	{
		while (mini->env[i])
		{
			printf("%s\n", mini->env[i]);
			i++;
		}
		printf("\n");
	}
	else if (strcmp(mini->toks[0], "export") == 0);
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
		mini->env = unset_cmd(mini->env, mini->toks[1]);
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
		//cambiare la variabile d'ambiente PWD nell'env
	}
	else if	(strcmp(mini->toks[0], "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0)); // questo oppure cerca nell'envp la variabile PWD e la printa
	else
		return (1);
	return (0);
}*/

int	builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**a;
	int		g_status;

	while (cmd)
	{
		a = ((t_mini *)cmd->content)->toks;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_status = my_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_status = my_cd(prompt);
		//else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			//g_status = my_export(prompt);
		//else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
		//	g_status = my_unset(prompt);
		//else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			//exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}

int	is_builtin(t_mini *n)
{
	int		l;

	if (!n->toks)
		return (0);
	if ((n->toks && ft_strchr(*n->toks, '/')) || (n->env && \
		ft_strchr(*n->env, '/')))
		return (0);
	l = ft_strlen(*n->toks);
	if (!ft_strncmp(*n->toks, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->toks, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->toks, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*n->toks, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*n->toks, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*n->toks, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*n->toks, "exit", l) && l == 4)
		return (1);
	return (0);
}
