/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 02:26:00 by ofadhel           #+#    #+#             */
/*   Updated: 2024/01/07 21:31:05 by ofadhel          ###   ########.fr       */
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
}				t_lexer;

typedef struct s_parser
{
	int				i; //parser toks
	int				j; //parser args
	int				k; //count_redirect
}				t_parser;

#endif
