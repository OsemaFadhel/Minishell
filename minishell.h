/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:21:15 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/27 14:46:03 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/* structs */

typedef struct s_cmds
{
	char	*cmd; //init to NULL
	char	**args;	//init to NULL
	char	*input; //init to NULL
	char	*output;	//init to NULL
}				t_cmds;

typedef struct s_mini
{
	t_list	*cmds;
	char	*history;
	char	**envp;
	char	**toks;
	char	*key;
	char	*value;
}				t_mini;

/* functions */

int		lexersplit(char *cmd, t_mini *mini);	//split the input into tokens
int		envdump(char **envp, t_mini *mini); //store envp in a struct

void	executor(t_mini	*mini); //execute the command

int		is_builtin(t_mini *mini, int i);
int		builtin(t_mini *mini, int i);
int		builtin_2(t_mini *mini, int i);
int		builtin_3(t_mini *mini, int i);


void	free_cmds(t_mini *mini, char *input); //free the cmds array and input given by readline

#endif
