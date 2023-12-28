/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:51:23 by ofadhel           #+#    #+#             */
/*   Updated: 2023/12/14 12:52:22 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

int	ft_isdigitalpha(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] < 'A' || c[i] > 'Z') && (c[i] < 'a' || c[i] > 'z') && \
		(c[i] < '0' || c[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

char	**expand_matrix(char **matrix, char *str) //for export command and maybe something else
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	new_matrix[i] = str;
	new_matrix[i + 1] = NULL;
	free(matrix);
	return (new_matrix);
}

char	**unset_cmd(char **matrix, char *str) //for unset builtin
{
	int		i;
	int		j;
	int		len;
	char	**new_matrix;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * i);
	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, len) != 0)
		{
			new_matrix[j] = matrix[i];
			j++;
		}
		i++;
	}
	new_matrix[j] = NULL;
	free(matrix);
	return (new_matrix);
}
