/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:47:59 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 18:15:42 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define _DEFAULT_SOURCE
# include <fcntl.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "lld_struct.h"
# include "libft.h"
# include "mlx.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILLURE 1
# define MLX_OFF 0
# define MLX_ON 1

# define GAME_NAME "Milk IT!"
# define ENTITIES_TYPE_COUNT 6
# define ALLOWED_ELEMS "01EPCA"

# define TILE 0
# define WALL 1
# define CHAR_RIGHT 1
# define CHAR_LEFT 2
# define CHAR_FRONT 3
# define CHAR_BACK 4
# define COLLECTIBLE 6
# define EXIT_OPEN 7
# define EXIT_SHUT 8

# define XPM_GROUND  "assets/xpm/Grass-1.xpm"
# define XPM_WALL  "assets/xpm/Bush.xpm"
# define XPM_EXIT  "assets/xpm/Chest-closed.xpm"
# define XPM_PLAYER  "assets/xpm/Cat-front.xpm"
# define XPM_COLLECTIBLE  "assets/xpm/Milk-full.xpm"
# define XPM_ADVERSE "assets/xpm/Cow-0.xpm"

# define RED_PIXEL 0xFF00FF
# define GREEN_PIXEL 0xFF00

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 500
# define TILE_SIZE 32
# define MOV_KEYS  (int[8]){XK_Right, XK_d, XK_Left, XK_a, XK_Up, XK_w, XK_Down, XK_s}


typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;


typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_count
{
	size_t	collectible;
	size_t	exit;
	size_t	player;
	size_t	adverse;
}	t_count;

typedef struct	s_map
{
	char			**grid;
	char			**shallow_grid;
	t_point			grid_size;
	size_t			row_size;
	size_t			col_size;
	t_entity		*wall;
	t_entity		*ground;
	t_entity		*collectible;
	t_entity		*exit;
	t_entity		*player;
	t_entity		*adverse;
	t_entity		*entities[ENTITIES_TYPE_COUNT + 1];
	char			valid_entities[ENTITIES_TYPE_COUNT + 1];
	void			*images[ENTITIES_TYPE_COUNT + 1];
	t_count			count;
	t_point			pchr_pos;
}	t_map;

typedef struct s_game
{
	t_img	img;
	t_map	map;
	void	*mlx;
	void	*win;
	size_t	mlx_state;
}			t_game;

int		parse_map(char *path, t_game *solong);
int		put_err(char *msg, t_game *solong, int mlx_instance);
int		render_loop(t_game *solong);
void	setup_hooks(t_game *solong);
int		destroy_mlx(t_game *solong);
char	**clean_grid(char **grid);
void	put_map(t_map *map, t_game *solong);
void	init_map_entities(t_map *map, t_entity *entities[], t_game *solong);
int		in_array(int val, int tab[], size_t siz);
int		close_game(t_game *solong, int mlx_instance);
#endif
