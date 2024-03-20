/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:11:08 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/18 10:11:09 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = ft_strlen(s);
	str = (char *)s;
	while (i >= 0)
	{
		if (str[i] == (char) c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
