/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:38:14 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/28 17:45:29 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute(t_mini *mini)
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

	for (i = 0; i < numsimplecommands; i++)
	{
		// Redirect input
		dup2(fdin, 0);
		close(fdin);

		// Setup output
		if (i == numsimplecommands - 1) {
			// Last simple command
			if (outfile)
			{
				fdout = open(outfile, /* mode */);
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
			execve(scmd[i].args[0], scmd[i].args);
			perror("execvp");
			exit(1);
		}
	} // for

	// Restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	if (!background)
	{
		// Wait for the last command
		waitpid(ret, NULL);
	}
}
// execute
