/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:09:25 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:15 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	while (i < n)
	{
		*d++ = *s++;
		i++;
	}
	return (dst);
}
