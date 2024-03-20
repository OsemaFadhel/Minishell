/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:07:24 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:07 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	p = (void *)malloc(nmemb * size);
	if (!p)
	{
		return (NULL);
	}
	ft_bzero(p, (nmemb * size));
	return (p);
}
