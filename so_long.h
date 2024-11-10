/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:47:59 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/10 19:20:00 by epinaud          ###   ########.fr       */
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

# define GAME_NAME "Milk IT!"
# define ENTITIES_TCOUNT 10
# define ALLOWED_ELEMS "01PECA"

# define TILE_ID 0
# define WALL_ID 1
# define CHAR_RGT_ID 6
# define CHAR_LFT_ID 7
# define CHAR_BCK_ID 8
# define CHAR_FRT_ID 2
# define EXIT_OPEN_ID 9
# define EXIT_SHUT_ID 3
# define CLCTBL_ID 4
# define ADVERSE_ID 5

# define XPM_GROUND  "assets/xpm/Grass-1.xpm"
# define XPM_WALL  "assets/xpm/Bush.xpm"
# define XPM_EXIT_SHUT  "assets/xpm/Chest-closed.xpm"
# define XPM_EXIT_OPEN  "assets/xpm/Chest-closed.xpm"
# define XPM_PLAYER_FRONT  "assets/xpm/Cat-front.xpm"
# define XPM_PLAYER_BACK  "assets/xpm/Cat-back.xpm"
# define XPM_PLAYER_LEFT  "assets/xpm/Cat-left.xpm"
# define XPM_PLAYER_RIGHT  "assets/xpm/Cat-right.xpm"
# define XPM_COLLECTIBLE  "assets/xpm/Milk-full.xpm"
# define XPM_ADVERSE "assets/xpm/Cow-0.xpm"

# define ENTITIES_ID (int[ENTITIES_TCOUNT]){TILE_ID, WALL_ID, EXIT_SHUT_ID, \
			EXIT_OPEN_ID, CHAR_RGT_ID, CHAR_LFT_ID, CHAR_BCK_ID, CHAR_FRT_ID, \
			CLCTBL_ID, ADVERSE_ID}
# define XPM_LST (char*[255]){XPM_GROUND, XPM_WALL, XPM_EXIT_SHUT, \
			XPM_EXIT_OPEN, XPM_PLAYER_RIGHT, XPM_PLAYER_LEFT, XPM_PLAYER_BACK, \
			XPM_PLAYER_FRONT, XPM_COLLECTIBLE, XPM_ADVERSE}
// # define RED_PIXEL 0xFF00FF
// # define GREEN_PIXEL 0xFF00
# define COUNTER_BGCLR 0XFFFFFF

# define WIN_OFFST_INCOL 1
# define WIN_OFFST_INRW 2
# define TILE_SIZE 32
# define CNTR_SIZ_INRW 1
# define MOV_KEYS  (int[8]){XK_Right, XK_d, XK_Left, XK_a, XK_Up, XK_w, XK_Down, XK_s}
# define PRV_POS 0
# define CUR_POS 1
# define NXT_POS 2

# define ERR_F_PATH_PERMS "Wrong path or insufficient permissions"

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
	void	*img;
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
	t_entity		*entities[ENTITIES_TCOUNT + 1];
	void			*images[ENTITIES_TCOUNT + 1];
	char			valid_entities[ENTITIES_TCOUNT + 1];
	t_count			count;
	t_point			pchr_pos;
	t_point			exit_pos;
}	t_map;

typedef struct s_game
{
	t_img	shape;
	t_map	map;
	void	*mlx;
	void	*win;
	size_t	mlx_state;
}			t_game;

int			put_err(char *msg, t_game *solong);
int			close_game(char *closure_msg, t_game *solong);
int			parse_map(char *path, t_game *solong);
void		put_map(t_map *map, t_game *solong);
void		setup_hooks(t_game *solong);
void		init_map_entities(t_map *map, t_entity *entities[], t_game *solong);
t_entity	*fetch_entity(char c, t_game *solong);
int			in_array(int val, int tab[], size_t siz);
char		**clean_grid(char **grid);
int			render_loop(t_game *solong);
int			render_rect(t_img *img, t_rect rect);
void		render_tile(t_point cur, t_game *solong);
void		render_exit(size_t items_got, t_game *solong);
void		render_entity(int entity_id, t_point cur, t_game *solong);
void		render_steps_count(size_t steps, t_game *solong);
#endif
