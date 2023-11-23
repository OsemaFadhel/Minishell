/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:21:15 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/21 15:46:44 by ofadhel          ###   ########.fr       */
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

typedef struct s_mini
{
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

void	free_cmds(t_mini *mini, char *input); //free the cmds array and input given by readline

#endif
