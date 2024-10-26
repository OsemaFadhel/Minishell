# Minishell <h2 align='right'>Final Grade 98/125 ✅ </h2>

This project is about creating a simple shell.

<h2 align="center"> <img src="https://github.com/OsemaFadhel/OsemaFadhel/blob/main/img/1712000100607257.gif" width="1080" height="400" /> </h2>

<h2 align="center"> Installation </h2>

```bash
#clone the repo
git clone https://github.com/OsemaFadhel/Minishell.git
cd Minishell

#compile and run the shell
make && ./minishell

```

## Lexer
The lexer in the Minishell project is responsible for breaking down the input command into tokens. It handles different types of characters and symbols such as spaces, quotes, and redirection operators. The lexer ensures that tokens are correctly identified and stored for further processing.

Key functionalities:

 - Token Splitting: The lexer splits the command into tokens based on spaces and special characters.
 - Handling Quotes: It manages double and single quotes to ensure that quoted strings are treated as single tokens.
 - Redirection and Pipes: The lexer identifies redirection operators (>, >>, <, <<) and pipes (|).

Example file: lexer.c

## Parser
The parser's role is to take the tokens produced by the lexer and construct a meaningful structure ([cmds in minishell.h](https://github.com/OsemaFadhel/Minishell/blob/main/include/minishell.h#L51)). It organizes the tokens into command structures, handling the relationships between different parts of the command.

Key functionalities:

 - Initialization: Initializes command structures and prepares them for execution.
 - Argument and Redirection Counting: Counts the number of arguments and redirections for each command.
 - Command Structuring: Constructs commands and associates arguments and redirections.

```c
typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	t_redirect		*redirect;
	int				out;
	int				in;
	int				redirect_count;
	struct s_cmds	*next;
}
```

Example file: parser.c

## Executor
The executor's job is to execute the parsed commands. It handles the actual running of commands, managing input/output redirections, pipes, and other execution-related tasks.

Key functionalities:

 - Path Management: Finds the correct path for executables.
 - Fork and Execute: Uses fork() and execve() to run commands in new processes.
 - Pipe and Redirection Handling: Manages pipes and redirections to ensure commands have the correct input and output.
Example file: executor.c

These components (lexer, parser, and executor) work together to take user input, interpret it correctly, and execute the commands as intended in the Minishell.
