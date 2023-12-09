/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:21:15 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/29 14:25:15 by ofadhel          ###   ########.fr       */
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
	char	*infile; 
	char	*outfile;
	int	redirect_type;
}				t_cmds;

typedef struct s_mini
{
	t_list	*cmds;
	int		cmds_count;
	char	*input; //init to NULL
	char	*output; //init to NULL
	char	*history;
	char	**envp;
	char	**toks;

}				t_mini;

/* functions */
/* main.c */

int		envdump(char **envp, t_mini *mini); //store envp in a struct
void	free_cmds(t_mini *mini, char *input); //free the cmds array and input given by readline

/* lexer.c */

int		lexersplit(char *cmd, t_mini *mini);	//split the input into tokens

/* executortest.c */

void	executor(t_mini	*mini); //execute the command

/* utils.c */

int		ft_isdigitalpha(char *c);
char		**unset_cmd(char **matrix, char *str); //unset the command
char		**expand_matrix(char **matrix, char *str); //expand the matrix

/* builtin.c */

int			is_builtin(t_mini *mini, int i); //check if the command is a builtin
int			builtin(t_mini *mini, int i);
int			builtin_2(t_mini *mini, int i);
int			builtin_3(t_mini *mini, int i);

/* signals.c */

void	sig_ignore(void); //ignore signals from keyboard
void	sig_handler(int signo); //handle signals from keyboard

#endif
