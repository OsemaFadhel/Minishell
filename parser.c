/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:55:37 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/20 15:36:23 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

t_cmds *create_cmds(char *cmd, char **args, char *infile, char *outfile, int redirect_type)
{
    t_cmds *new_cmds = malloc(sizeof(t_cmds));
    if (!new_cmds) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    new_cmds->cmd = strdup(cmd);

    if (args != NULL) {
        int args_count = 0;
        while (args[args_count] != NULL) {
            args_count++;
        }
        new_cmds->args = malloc((args_count + 1) * sizeof(char *));
        if (!new_cmds->args) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < args_count; i++) {
            new_cmds->args[i] = strdup(args[i]);
        }
        new_cmds->args[args_count] = NULL; // Null-terminate the args array
    } else {
        new_cmds->args = NULL;
    }

    new_cmds->infile = (infile != NULL) ? strdup(infile) : NULL;
    new_cmds->outfile = (outfile != NULL) ? strdup(outfile) : NULL;
    new_cmds->redirect_type = redirect_type;
    new_cmds->next = NULL; // Initialize next pointer to NULL

    return new_cmds;
}

void push_back(t_cmds **head, t_cmds *new_cmds) {
    if (*head == NULL) {
        *head = new_cmds;
    } else {
        t_cmds *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_cmds;
    }
}

void fill_list_from_matrix(char **lexer, int lexer_size, t_cmds **head) {
    t_cmds *current_cmds = NULL;
    char *cmd = NULL;
    char **args = NULL;
    char *infile = NULL;
    char *outfile = NULL;
    int redirect_type = 0;

    for (int i = 0; i < lexer_size; i++) {
        if (strcmp(lexer[i], "|") == 0) {
            // Pipe encountered, move to the next node
            if (current_cmds != NULL) {
                push_back(head, current_cmds);
            }
            current_cmds = NULL;
        } else if (strcmp(lexer[i], ">") == 0) {
            // Output redirection
            outfile = lexer[i + 1];
            redirect_type = 1; // '>'
            i++; // Skip the next token since it is the outfile
        } else if (strcmp(lexer[i], ">>") == 0) {
            // Output redirection (append)
            outfile = lexer[i + 1];
            redirect_type = 2; // '>>'
            i++; // Skip the next token since it is the outfile
        } else if (strcmp(lexer[i], "<") == 0) {
            // Input redirection
            infile = lexer[i + 1];
            redirect_type = 3; // '<'
            i++; // Skip the next token since it is the infile
        } else if (strcmp(lexer[i], "<<") == 0) {
            // Input redirection (here document)
            infile = lexer[i + 1];
            redirect_type = 4; // '<<'
            i++; // Skip the next token since it is the infile
        } else {
            // Either command or argument
            if (cmd == NULL) {
                cmd = lexer[i];
            } else {
                // Argument
                int args_count = 0;
                while (lexer[i] != NULL && strcmp(lexer[i], "|") != 0 &&
                       strcmp(lexer[i], ">") != 0 && strcmp(lexer[i], ">>") != 0 &&
                       strcmp(lexer[i], "<") != 0 && strcmp(lexer[i], "<<") != 0) {
                    args_count++;
                    i++;
                }

                args = malloc((args_count + 1) * sizeof(char *));
                if (!args) {
                    perror("Memory allocation error");
                    exit(EXIT_FAILURE);
                }

                int arg_index = 0;
                i -= args_count + 1; // Reset the index to start of the arguments
                while (arg_index < args_count) {
                    args[arg_index] = lexer[i];
                    arg_index++;
                    i++;
                }
                args[arg_index] = NULL; // Null-terminate the args array

                i--; // Compensate for the extra increment in the outer loop
            }
        }
    }

    // Add the last command to the list
    if (cmd != NULL) {
        current_cmds = create_cmds(cmd, args, infile, outfile, redirect_type);
        push_back(head, current_cmds);
    }
}

void free_cmds_list(t_cmds *head) {
    t_cmds *current = head;
    while (current != NULL) {
        t_cmds *next = current->next;

        free(current->cmd);
        if (current->args != NULL) {
            for (int i = 0; current->args[i] != NULL; i++) {
                free(current->args[i]);
            }
            free(current->args);
        }
        free(current->infile);
        free(current->outfile);
        free(current);

        current = next;
    }
}

void free_mini(t_mini *my_mini) {
    free_cmds_list(my_mini->cmds);
    free(my_mini->input);
    free(my_mini->output);
    free(my_mini->history);
    // Free other allocated memory in t_mini if any
    free(my_mini);
}

/*int main() {
    char *lexer[] = {"echo", "ciao", "> file.txt", "|", "grep", "a"};
    int lexer_size = sizeof(lexer) / sizeof(lexer[0]);

    t_mini *my_mini = malloc(sizeof(t_mini));
    if (!my_mini) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    my_mini->cmds = NULL; // Initialize the linked list
    my_mini->cmds_count = 0;
    my_mini->input = NULL;
    my_mini->output = NULL;
    my_mini->history = NULL;
    my_mini->env = NULL;
    my_mini->toks = lexer; // Assuming toks is initialized to the lexer matrix

    fill_list_from_matrix(my_mini->toks, lexer_size, &(my_mini->cmds));

    // Now 'my_mini->cmds' contains the linked list of t_cmds structures

    // Access the list elements*/

void	init_cmds(t_cmds *cmds)
{
	cmds->cmd = NULL;
	cmds->args = NULL;
	cmds->infile = NULL;
	cmds->outfile = NULL;
	cmds->redirect_type = 0;
	cmds->next = NULL;
}

int	parser(t_mini *mini, t_cmds **cmds)
{

}
