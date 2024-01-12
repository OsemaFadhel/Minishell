#ifndef BUILTIN_H
# define BUILTIN_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

# define ERROR		-1

# define PROMPT 	"$> "
# define SHELL_NAME	"minishell"
# define DEBUG_ENV	"DEBUG"

extern char	**g_env;

struct s_builtins_list
{
	char	*name;
	int		(*func)(int argc, char **argv);
};

typedef struct builtins_s_list
{
	void			*content;
	struct s_list	*next;
}					builtins_t_list;

// BUILTIN
int	builtins_check(char **argv);
int	builtins_exec(char **argv, bool subshell, t_list *l_free);

// BUILTIN_CD
int	builtins_cd(int argc, char **argv);

// BUILTIN_ECHO
int	builtins_echo(int argc, char **argv);

// BUILTIN_ENV
int	builtins_env(int argc, char **argv);

// BUILTIN_EXIT
int	builtins_exit(int argc, char **argv, bool subshell, t_list *l_free);

// BUILTIN_EXPORT
int	builtins_export(int argc, char **argv);

// BUILTIN_PWD
int	builtins_pwd(int argc, char **argv);

// BUILTIN_UNSET
int	builtins_unset(int argc, char **argv);

#endif