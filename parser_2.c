/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:30:52 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/20 15:43:42 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

// Function to create a new t_cmds structure
t_cmds *create_cmds(char *cmd, char **args, char *infile, char *outfile, int redirect_type)
{
    t_cmds *new_cmds = malloc(sizeof(t_cmds));
    if (!new_cmds)
        return NULL;

    new_cmds->cmd = strdup(cmd);

    if (args != NULL) {
        int args_count = 0;
        while (args[args_count] != NULL)
            args_count++;

        new_cmds->args = malloc((args_count + 1) * sizeof(char *));
        if (!new_cmds->args) {
            free(new_cmds->cmd);
            free(new_cmds);
            return NULL;
        }

        for (int i = 0; i < args_count; i++)
            new_cmds->args[i] = strdup(args[i]);

        new_cmds->args[args_count] = NULL;
    } else {
        new_cmds->args = NULL;
    }

    new_cmds->infile = (infile != NULL) ? strdup(infile) : NULL;
    new_cmds->outfile = (outfile != NULL) ? strdup(outfile) : NULL;
    new_cmds->redirect_type = redirect_type;
    new_cmds->next = NULL;

    return new_cmds;
}

void push_back(t_cmds **head, t_cmds *new_cmds)
{
    if (*head == NULL) {
        *head = new_cmds;
    } else {
        t_cmds *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = new_cmds;
    }
}

void fill_list_from_matrix(char **lexer, int lexer_size, t_cmds **head)
{
    t_cmds *current_cmd = NULL;
    char *cmd = NULL;
    char **args = NULL;
    char *infile = NULL;
    char *outfile = NULL;
    int redirect_type = 0;

    for (int i = 0; i < lexer_size; i++) {
        if (strcmp(lexer[i], "|") == 0) {
            if (current_cmd != NULL)
                push_back(head, current_cmd);
            current_cmd = NULL;
        } else if (strcmp(lexer[i], ">") == 0) {
            outfile = lexer[i + 1];
            redirect_type = 1;
            i++;
        } else if (strcmp(lexer[i], ">>") == 0) {
            outfile = lexer[i + 1];
            redirect_type = 2;
            i++;
        } else if (strcmp(lexer[i], "<") == 0) {
            infile = lexer[i + 1];
            redirect_type = 3;
            i++;
        } else if (strcmp(lexer[i], "<<") == 0) {
            infile = lexer[i + 1];
            redirect_type = 4;
            i++;
        } else {
            if (cmd == NULL)
                cmd = lexer[i];
            else {
                int args_count = 0;
                while (lexer[i] != NULL && strcmp(lexer[i], "|") != 0 &&
                       strcmp(lexer[i], ">") != 0 && strcmp(lexer[i], ">>") != 0 &&
                       strcmp(lexer[i], "<") != 0 && strcmp(lexer[i], "<<") != 0) {
                    args_count++;
                    i++;
                }

                args = malloc((args_count + 1) * sizeof(char *));
                if (!args) {
                    free(cmd);
                    free(current_cmd);
                    return;
                }

                int arg_index = 0;
                i -= args_count + 1;
                while (arg_index < args_count) {
                    args[arg_index] = lexer[i];
                    arg_index++;
                    i++;
                }
                args[arg_index] = NULL;
                i--;
            }
        }
    }

    if (cmd != NULL) {
        current_cmd = create_cmds(cmd, args, infile, outfile, redirect_type);
        push_back(head, current_cmd);
    }
}

void free_cmds_list(t_cmds *head)
{
    t_cmds *current = head;
    while (current != NULL) {
        t_cmds *next = current->next;

        free(current->cmd);
        if (current->args != NULL) {
            for (int i = 0; current->args[i] != NULL; i++)
                free(current->args[i]);

            free(current->args);
        }
        free(current->infile);
        free(current->outfile);
        free(current);

        current = next;
    }
}


int	parser(t_mini *mini, t_cmds **cmds)
{
    int	i;

    i = 0;
    fill_list_from_matrix(mini->toks, cmds);
}

// Function to free the memory of the t_mini structure
