/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/31 23:14:08 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/* void	execute(t_mini *mini)
{
	// Save in/out
	int tmpin = dup(0);
	int tmpout = dup(1);

	// Set the initial input
	int fdin;
	if (infile)
	{
		fdin = open(infile, O_READ);
	}
	else
	{
		// Use default input
		fdin = dup(tmpin);
	}

	int ret;
	int fdout;
	int i = 0;
	while (i <= cmd_count)
	{
		// Redirect input
		dup2(fdin, 0);
		close(fdin);

		// Setup output
		if (i == numsimplecommands - 1) {
			// Last simple command
			if (outfile)
			{
				fdout = open(outfile, );
			}
			else
			{
				// Use default output
				fdout = dup(tmpout);
			}
		}
		else
		{
			// Not last simple command
			// Create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}

		// Redirect output
		dup2(fdout, 1);
		close(fdout);

		// Create child process
		ret = fork();
		if (ret == 0)
		{
			executor(mini, mini->cmds); // old executor
			perror("BASH$");
			exit(1);
		}
		i++;
	} // for

	// Restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	if (!background) //if (1)
	{
		// Wait for the last command
		waitpid(ret, NULL);
	}
} */
// execute
/*void execute(t_mini *mini)
{
    // Save in/out
    int tmpin = dup(0);
    int tmpout = dup(1);
	t_cmds *cmd = mini->cmds;

    // Set the initial input
	int	i = 0;
	while (cmd->redirect[i])
	{
		if (cmd.redirect[i]->redirect_type == 3)
		{
			cmd.fdi = open(cmd.redirect[i]->infile, O_RDONLY);
		}
		else
		{
			// Use default input
			cmd.fdi = dup(tmpin);
		}
		i++;
	}

    int ret;
    while (cmd != NULL)
    {
        // Redirect input
        dup2(fdin, 0);
        close(fdin);

        // Setup output
		i = 0;
		while (cmd.redirect[i])
		{
			if (cmd.redirect[i]->redirect_type == 1)
			{
				cmd.fdo = open(cmd.redirect[i]->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			}
			else if (cmd.redirect[i]->redirect_type == 2)
			{
				cmd.fdo = open(cmd.redirect[i]->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
			}
			else
			{
				// Use default input
				cmd.fdo = dup(tmpout);
			}
			i++;
		}
        else
        {
            // Not the last command
            // Create pipe
            int fdpipe[2];
            pipe(fdpipe);
			cmd.fdo = fdpipe[1];
            cmd.fdi = fdpipe[0];
        }

        // Redirect output
        dup2(cmd.fdo, 1);
        close(cmd.fdo);

        // Create child process
        ret = fork();
        if (ret == 0)
        {
            executor(mini, cmd); // Call the executor with the current command
            perror("BASH$");
            exit(1);
        }
        cmd = cmd->next;
    }

    // Restore in/out defaults
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

    waitpid(ret, NULL);
}*/

void execute(t_mini *mini)
{
    // Save in/out
    int tmpin = dup(0);
    int tmpout = dup(1);

    int ret;
    t_cmds *current_cmd = mini->cmds;

	int i = 0;
	while (mini->cmds->redirect[i].redirect_type != 0)
	{
		if (mini->cmds->redirect[i].redirect_type == 3)
		{
			mini->cmds->fdi = open(mini->cmds->redirect[i].infile, O_RDONLY);
		}
		else
		{
			// Use default input
			mini->cmds->fdi = dup(tmpin);
		}
		i++;
	}
	mini->cmds->fdi = dup(tmpin);
	while (current_cmd != NULL)
	{
		// Redirect input
		dup2(mini->cmds->fdi, 0);
		close(mini->cmds->fdi);

        // Setup output
		i = 0;
		while (mini->cmds->redirect[i].redirect_type != 0)
		{
			printf("mini->cmds->redirect[i].redirect_type = %d\n", mini->cmds->redirect[i].redirect_type);
		    if (mini->cmds->redirect[i].redirect_type == 1)
		    {
		        mini->cmds->fdo = open(mini->cmds->redirect[i].outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		    }
		    else if (mini->cmds->redirect[i].redirect_type == 2)
		    {
    	        mini->cmds->fdo = open(mini->cmds->redirect[i].outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
    	    }
    	    else
    	    {
    	        // Use default output
    	        mini->cmds->fdo = dup(tmpout);
    	    }
    	    i++;
    	}
		mini->cmds->fdo = dup(tmpout);
    	/*int fdpipe[2]; // Create pipe
    	pipe(fdpipe);
    	mini->cmds->fdo = fdpipe[1];
    	mini->cmds->fdi = fdpipe[0];
    	dup2(mini->cmds->fdo, 1);  // Redirect output
    	close(mini->cmds->fdo);*/
		printf("mini->cmds->fdo = %d\n", mini->cmds->fdo);
        // Create child process
		ret = fork();
    	if (ret == 0)
    	{
    	    executor(mini, current_cmd); // Call the executor with the current command
    	    perror("BASH$");
    	    exit(1);
    	}
    	current_cmd = current_cmd->next;
	}
    // Restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	while (waitpid(-1, NULL, 0) > 0);
}

