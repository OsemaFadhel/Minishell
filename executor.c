/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:30:52 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/19 21:50:58 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	redirect(...)
{
	int		fd;

	fd = open("<name of file>", O_RDWR | 0_CREAT, 0777); // check man 2 open
	dup2(fd, /* what is gonna be written in the file*/); // 0 is stdin, 1 is stdout, 2 is stderr(same as 1)
	// or maybe write(fd, "something", ft_strlen("something"));
	close(fd);
}
