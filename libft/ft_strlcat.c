/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:10:42 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:23 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	d;
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (slen);
	d = ft_strlen(dst);
	dlen = d;
	if (dstsize <= dlen)
		return (dstsize + slen);
	s = 0;
	while (src[s] && d + 1 < dstsize)
	{
		dst[d] = src[s];
		s++;
		d++;
	}
	dst[d] = 0;
	return (dlen + slen);
}
