/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:47:59 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/21 16:33:50 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define TILE 0
# define WALL 1
# define CHAR_BACK 2
# define CHAR_FRONT 3
# define CHAR_RIGHT 4
# define CHAR_LEFT 5
# define COLLECTIBLE 6
# define EXIT_OPEN 7
# define EXIT_SHUT 8

# define RED_PIXEL 0xFF00FF
# define GREEN_PIXEL 0xFF00

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*sprites[9];
	t_img	img;
}			t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

#endif