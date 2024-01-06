/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:21:15 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/06 22:03:43 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
#include <sys/stat.h>
# include "lexer.h"


/* global variables */



/* structs */

typedef struct s_redirect
{
	char	*infile; // <, << is delimeter
	char	*outfile; // >, >>
	int		redirect_type; // 1 >, 2 >>, 3 <, 4 <<
}				t_redirect;

typedef struct s_cmds
{
	char			*cmd; //init to NULL
	char			**args;	//init to NULL
	t_redirect		*redirect;
	int				out;
	int				in;
	int				redirect_count;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_mini
{
	t_cmds	*cmds;
	int		cmds_count;
	int		fdin; //init to NULL
	int		fdout; //init to NULL
	int		here_doc_flag; //init to 0
	char	**env;
	char	**toks;
}				t_mini;

/* functions */
/* main.c */

int			envdump(char **envp, t_mini *mini); //store envp in a struct
void		free_cmds(t_mini *mini, char *input); //free the cmds array and input given by readline

/* lexer.c */

int			lexersplit(char *cmd, t_mini *mini);	//split the input into tokens
char		**lexersplit_1(char *cmd, t_mini *mini, t_lexer *lexer); //split cmd into tokens taking care of spaces and quotes. anything inside quotes count as one word
int			check_closed_dquotes(char *cmd, int i);
int			check_closed_quotes(char *cmd, int i);
int			count_words_2(char *cmd, int i, int words);
int			count_words_3(char *cmd, int i, int words);
int			count_words_lex(char *cmd);
int			add_str_dquot(char *cmd, char **toks, t_lexer *lexer, char **env);
int			add_str_quot(char *cmd, char **toks, t_lexer *lexer);
int			add_str(char *cmd, char **toks, t_lexer *lexer, char **env);
void		change_env_v(char *cmd, char **toks, t_lexer *lexer, char **env);

/* Parser */

int			parser(t_mini *mini);

/* executortest.c */

void		executor(t_mini	*mini, t_cmds *cmds); //execute the command
void 		execute(t_mini *mini);

/* utils.c */

int			ft_isdigitalpha(char *c);
char		**unset_cmd(char **matrix, char *str); //unset the command
char		**expand_matrix(char **matrix, char *str); //expand the matrix

/* builtin.c */

int			is_builtin(t_mini *mini, t_cmds *cmds, int i); //check if the command is a builtin
int			builtin(t_mini *mini, int i);
int			builtin_2(t_mini *mini, int i);
int			builtin_3(t_mini *mini, int i);

/* signals.c */

void		sig_ignore(t_mini *mini); //ignore signals from keyboard
void		sig_handler(int signo); //handle signals from keyboard

#endif
