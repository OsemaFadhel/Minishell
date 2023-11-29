/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:30 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/29 13:53:44 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_ignore(void) // ignore signals from keyboard
{
	signal(SIGINT, SIG_IGN); // ctrl + c; arg sig_ign means ignore
	signal(SIGQUIT, SIG_IGN); // ctrl + \;
	signal(SIGTSTP, SIG_IGN); // ctrl + z;
}
