/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:30 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/09 10:40:22 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_ctrlc(int sign)
{
	if (sign == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_ctrld(char *line, t_mini *mini)
{
	ft_free_array(mini->env);
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_status);
}

void	sig_ignore(void) // ignore signals from keyboard
{
	signal(SIGINT, ft_ctrlc); // ctrl + c; arg sig_ign means ignore
	signal(SIGQUIT, SIG_IGN); // ctrl + \;
	signal(SIGTSTP, SIG_IGN); // ctrl + z;
}
