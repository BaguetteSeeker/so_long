/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <epinaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:47:59 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/22 17:16:46 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
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

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct  s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct	s_counter
{
	size_t	player;
	size_t	adverse;
	size_t	collectibles;
	size_t	exit;
}	t_counter;

typedef struct	s_adverse
{
	t_point	pos;
}	t_adverse;

typedef struct	s_collectible
{
	t_point	pos;
}	t_collectible;

typedef struct s_err
{
	
} t_err ;


typedef struct	s_map
{
	t_counter		count;
	t_point			player;
	t_point			exit;
	t_adverse		adverse[1];
	t_collectible	collectible[2];
	size_t			row_size;
	size_t			col_size;
	size_t			size;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*sprites[9];
	t_img	img;
	t_map	map;
}			t_game;

int		parse_map(char *path);
int		put_err(char *msg, t_game *solong);
int		render_loop(t_game *solong);
void	setup_hooks(t_game *solong);
int		on_destroy(t_game *solong);
#endif