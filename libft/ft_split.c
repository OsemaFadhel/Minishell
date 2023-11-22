/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:03:26 by ofadhel           #+#    #+#             */
/*   Updated: 2023/11/21 19:02:29 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


// int	count_words(char const *s, char c)
// {
// 	int	words;
// 	int	i;

// 	i = 0;
// 	words = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			words++;
// 			while (s[i] != c && s[i])
// 			{
// 				i++;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	return (words);
// }

// char	*strsub(char const *s, unsigned int start, size_t len)
// {
// 	size_t	j;
// 	char	*str;

// 	str = malloc(sizeof(char) * (len - start + 1));
// 	if (!str)
// 		return (NULL);
// 	j = 0;
// 	while (start < len)
// 	{
// 		str[j] = s[start];
// 		j++;
// 		start++;
// 	}
// 	str[j] = 0;
// 	return (str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	int		index;
// 	char	**split;

// 	split = malloc((count_words(s, c) + 1) * sizeof(char *));
// 	if (!s || !split)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	index = -1;
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] != c && index < 0)
// 			index = i;
// 		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
// 		{
// 			split[j] = strsub(s, index, i);
// 			index = -1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	split[j] = 0;
// 	return (split);
// }

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int count_words(char const *s, char c)
{
    int words = 0;
    int in_quotes = 0;
    int i = 0;

    while (s[i])
    {
        if ((s[i] == '\'' || s[i] == '\"') && !in_quotes)
        {
            in_quotes = 1;
            i++;
        }
        else if ((s[i] == '\'' || s[i] == '\"') && in_quotes)
        {
            in_quotes = 0;
            i++;
        }
        else if (!is_whitespace(s[i]) && !in_quotes)
        {
            words++;
            while (s[i] && !is_whitespace(s[i]) && !((s[i] == '\'' || s[i] == '\"') && in_quotes))
            {
                i++;
            }
        }
        else
            i++;
    }

    return words;
}

static char *strsub(char const *s, unsigned int start, size_t len)
{
    char *str = malloc(sizeof(char) * (len - start + 2));
    if (!str)
        return NULL;

    size_t j = 0;
    while (start <= len)
    {
        str[j] = s[start];
        j++;
        start++;
    }
    str[j] = '\0';
    return str;
}

char **ft_split(char const *s, char c)
{
    if (!s)
        return NULL;

    size_t i = 0;
    size_t j = 0;
    int in_quotes = 0;
    int index = -1;

    char **split = malloc((count_words(s, c) + 1) * sizeof(char *));
    if (!split)
        return NULL;

    while (s[i])
    {
        if ((s[i] == '\'' || s[i] == '\"') && !in_quotes)
        {
            in_quotes = 1;
            index = i;
            i++;
        }
        else if ((s[i] == '\'' || s[i] == '\"') && in_quotes)
        {
            in_quotes = 0;
            split[j++] = strsub(s, index, i - 1);
            i++;
        }
        else if (!is_whitespace(s[i]) && !in_quotes)
        {
            index = i;
            while (s[i] && !is_whitespace(s[i]) && !((s[i] == '\'' || s[i] == '\"') && in_quotes))
            {
                i++;
            }
            split[j++] = strsub(s, index, i - 1);
        }
        else
            i++;
    }

    split[j] = NULL;
    return split;
}