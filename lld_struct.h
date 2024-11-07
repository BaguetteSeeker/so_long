/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:30:59 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/07 18:21:34 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLD_STRUCT_H
# define LLD_STRUCT_H
# include "stdlib.h"

typedef struct  s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct	s_entity
{
	char			xpm[255];
	void			*img;
	int				imgwdth;
	int				imghght;
	size_t			count;
	t_point			pos;
	struct s_entity	*next;
}	t_entity;

# ifndef LL_TYP
# 	define LL_TYP t_entity
# endif
#endif