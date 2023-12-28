/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:54:05 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/14 12:54:53 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect(...)
{
	int		fd;

	if ( >>)
		//fd = open("<name of file>", O_RDWR | 0_CREATE || 0_APPEND , 0777); // check man 2 open
	if (>)
		//fd = open("<name of file>", O_RDWR | 0_CREATE, 0777)
	dup2(fd, /* what is gonna be written in the file*/); // 0 is stdin, 1 is stdout, 2 is stderr(same as 1)
	// or maybe write(fd, "something", ft_strlen("something"));
	close(fd);
}
