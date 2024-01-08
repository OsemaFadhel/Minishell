/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:30 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/08 20:36:38 by ofadhel          ###   ########.fr       */
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
	g_exit_status = 1;
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	sig_ignore(void) // ignore signals from keyboard
{
	signal(SIGINT, ft_ctrlc); // ctrl + c; arg sig_ign means ignore
	//signal(SIGTERM, ft_ctrld); // ctrl + d;
	signal(SIGQUIT, SIG_IGN); // ctrl + \;
	signal(SIGTSTP, SIG_IGN); // ctrl + z;
}

/*void	ft_signals(t_mini *mini)
{
	tcgetattr(STDIN_FILENO, &mini->tty_attrs);
	mini->tty_attrs.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->tty_attrs);
	mini->signal_nothing.sa_handler = ft_does_nothing;
	mini->signal_int.sa_handler = ft_head;
	mini->signal_quit.sa_handler = ft_handle_quit;
	mini->signal_nothing.sa_flags = SA_RESTART;
	mini->signal_int.sa_flags = SA_RESTART;
	mini->signal_quit.sa_flags = SA_RESTART;
	sigemptyset(&(mini->signal_nothing.sa_mask));
	sigemptyset(&(mini->signal_int.sa_mask));
	sigemptyset(&(mini->signal_quit.sa_mask));
	sigaction(SIGINT, &mini->signal_int, 0);
	sigaction(SIGQUIT, &mini->signal_quit, 0);
	sigaction(SIGTERM, &mini->signal_quit, 0);
}*/
