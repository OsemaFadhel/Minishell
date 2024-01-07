/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:30 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 04:25:12 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

//missing ctrl + d

void	sig_handler(int signo) // handle signals from keyboard
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0); //test on unix; replace line with empty string
		//rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(ft_itoa(signo), 2);
	}
}

void	sig_ignore(t_mini *mini) // ignore signals from keyboard
{
	signal(SIGINT, sig_handler); // ctrl + c; arg sig_ign means ignore
	signal(SIGQUIT, SIG_IGN); // ctrl + \;
	signal(SIGTSTP, SIG_IGN); // ctrl + z;
}
