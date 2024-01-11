/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:21:15 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/11 12:45:18 by ofadhel          ###   ########.fr       */
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
# include <sys/stat.h>
# include "utils.h"

/* global variables */
extern int	g_exit_status;

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
	int				out; //indicates if there is a redirection
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
	int		toks_count;
}				t_mini;

/* functions */
/* main.c */

int			envdump(char **envp, t_mini *mini); //store envp in a struct

/* free */

void		free_cmds(t_mini *mini, char *input);
void		ft_free_array(char **array);
void		free_cmds_list(t_cmds *head);
void		free_redirect(t_redirect *redirect);

/* lexer*/

int			lexersplit(char *cmd, t_mini *mini);
int			lexersplit_1(char *cmd, t_mini *mini, t_lexer *lexer);
int			check_closed_dquotes(char *cmd, int i);
int			check_closed_quotes(char *cmd, int i);
int			count_words_2(char *cmd, int i, int words);
int			count_words_3(char *cmd, int i, int words);
int			count_words_lex(char *cmd, t_lexer *lexer);
int			add_str_dquot(char *cmd, t_mini *mini, t_lexer *lexer, char **env);
int			add_str_quot(char *cmd, t_mini *mini, t_lexer *lexer);
int			add_str(char *cmd, t_mini *mini, t_lexer *lexer, char **env);
void		change_env_v(char *cmd, t_mini *mini, t_lexer *lexer, char **env);
int			add_env(t_mini *mini, t_lexer *lexer, char *cmd);
char		*get_env_var(char *tmp, char **env);
char		*get_env_name(char *cmd, int i);
void		add_pipe_char(char *cmd, t_mini *mini, t_lexer *lexer);
void		add_single_char(char *cmd, t_mini *mini, t_lexer *lexer);
void		add_redirect(char *cmd, t_mini *mini, t_lexer *lexer);

/* Parser */

void		init_cmds(t_cmds *cmds, t_mini *mini, t_parser *parser);
void		new_cmd(t_mini *mini, t_parser *parser, t_cmds *cmds);
void		init_parser(t_parser *parser, t_mini *mini, t_cmds *cmds);
int			is_redirect(char *str);
int			add_out_redirect(t_cmds *cmds, char **toks,
				t_parser *parser, int type);
int			add_in_redirect(t_cmds *cmds, char **toks,
				t_parser *parser, int type);
int			count_red_arg(t_mini *mini, int i);
int			count_args(t_mini *mini, t_parser *parser);
int			count_redirect(t_mini *mini, t_parser *parser);
void		sub_last_else(t_mini *mini, t_parser *parser, t_cmds *cmds);
int			parser(t_mini *mini);

/* executor */

void		executor(t_mini	*mini, t_cmds *cmds); //execute the command
char		*add_path(t_mini *mini, t_cmds *cmds, int i);
int			check_bin(t_mini *mini, t_cmds *cmds);
int			search_env(char **env, char *str);
void		execute(t_mini *mini);
void		set_pipes(t_mini *mini, t_cmds *current_cmd,
				int cmd_count, int tmpout);
void		restore_stds(int tmpin, int tmpout);
void		ft_fork(t_mini *mini, t_cmds *current_cmd, int tmpin, int tmpout);
void		here_doc(t_mini *mini, char *delimeter);
void		in_redirect(t_mini *mini, t_cmds *current_cmd);
void		out_redirect(t_mini *mini, t_cmds *current_cmd);
void		update_fd(t_mini *mini, t_cmds *current_cmd);

/* utils */

int			ft_isdigitalpha(char *c);
char		**unset_cmd(char **matrix, char *str); //unset the command
char		**expand_matrix(char **matrix, char *str); //expand the matrix
int			ft_strcmp(char *s1, char *s2);

/* builtin */

int			is_builtin(t_mini *mini, t_cmds *cmds, int i);
int			builtin(t_mini *mini, int i);
int			builtin_2(t_mini *mini, int i);
int			builtin_3(t_mini *mini, int i);

/* signals */

void		sig_ignore(void);
void		ft_ctrld(char *line, t_mini *mini);

#endif
