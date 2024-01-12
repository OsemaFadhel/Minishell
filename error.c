/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:53:18 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/12 16:56:54 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_error(int flag)
{
	if (flag == 1)
	{
		printf("Error: unclosed quotes\n");
		g_exit_status = 2;
	}
	if (flag == 2)
		printf("Error: No such file or directory\n");
	return (0);
}
