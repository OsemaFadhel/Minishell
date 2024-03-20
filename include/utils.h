/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabi-rac <dabi-rac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:06:36 by dabi-rac          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:02 by dabi-rac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_lexer
{
	int				i;
	int				j;
	int				k;
	int				l;
	int				words;
	int				flag;
}				t_lexer;

typedef struct s_parser
{
	int				i;
	int				j;
	int				k;
	int				l;
}				t_parser;

#endif
