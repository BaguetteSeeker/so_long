/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:47:59 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/12 19:25:13 by epinaud          ###   ########.fr       */
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
# define MIN_MAP_NMSIZ 10
# define ENTT_TCOUNT 10
# define ALLOWED_ELEMS "01PECA"
# define COUNTER_BGCLR 0XFFFFFF
# define TILE_SIZE 32
# define WIN_OFFST_INCOL 1
# define WIN_OFFST_INRW 2
# define CNTR_SIZ_INRW 1

# define TILE_ID 0
# define WALL_ID 1
# define CHAR_RGT_ID 7
# define CHAR_LFT_ID 8
# define CHAR_BCK_ID 9
# define CHAR_FRT_ID 2
# define EXIT_OPEN_ID 6
# define EXIT_SHUT_ID 3
# define CLCTBL_ID 5
# define ADVERSE_ID 4

# define XPM_GROUND  "assets/xpm/Grass-1.xpm"
# define XPM_WALL  "assets/xpm/Bush.xpm"
# define XPM_EXIT_SHUT  "assets/xpm/Chest-closed.xpm"
# define XPM_EXIT_OPEN  "assets/xpm/Chest-open.xpm"
# define XPM_PLAYER_FRONT  "assets/xpm/Cat-front.xpm"
# define XPM_PLAYER_BACK  "assets/xpm/Cat-back.xpm"
# define XPM_PLAYER_LEFT  "assets/xpm/Cat-left.xpm"
# define XPM_PLAYER_RIGHT  "assets/xpm/Cat-right.xpm"
# define XPM_COLLECTIBLE  "assets/xpm/Milk-full.xpm"
# define XPM_ADVERSE "assets/xpm/Cow-0.xpm"

# define ST_XPMS XPM_GROUND, XPM_WALL, XPM_PLAYER_FRONT, XPM_EXIT_SHUT
# define ND_XPMS XPM_COLLECTIBLE, XPM_ADVERSE, XPM_EXIT_OPEN
# define RD_XPMS XPM_PLAYER_RIGHT, XPM_PLAYER_LEFT, XPM_PLAYER_BACK
# define ST_IDS TILE_ID, WALL_ID, CHAR_FRT_ID, EXIT_SHUT_ID, CLCTBL_ID
# define ND_IDS ADVERSE_ID, EXIT_OPEN_ID, CHAR_RGT_ID, CHAR_LFT_ID, CHAR_BCK_ID
# define ENTITIES_ID (int[ENTT_TCOUNT]){ST_IDS, ND_IDS}
# define XPM_LST (char*[255]){ST_XPMS, ND_XPMS, RD_XPMS}

# define MOV_KEYS (int[8]){XK_Right,XK_Left,XK_Up,XK_Down,XK_d,XK_a,XK_w,XK_s}

# define ERR_F_PATH_PERMS "Wrong path or insufficient permissions"

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct s_img
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

typedef struct s_map
{
	char			**grid;
	char			**shallow_grid;
	t_point			grid_size;
	size_t			row_size;
	size_t			col_size;
	t_entity		*entities[ENTT_TCOUNT + 1];
	void			*images[ENTT_TCOUNT + 1];
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

int			parse_map(char *path, t_game *solong);
void		put_map(t_map *map, t_game *solong);
void		setup_hooks(t_game *solong);
void		load_xpms(t_entity *entities[], t_game *solong);
int			render_rect(t_img *img, t_rect rect);
void		render_tile(size_t xpm_id, t_point pos, t_game *solong);
void		render_steps_count(size_t steps, t_game *solong);
void		move_player(int keysym, t_point *curpos, t_game *solong);
int			put_err(char *msg, t_game *solong);
int			close_game(char *closure_msg, t_game *solong);
int			clean_game_memory(t_game *solong);
t_entity	*fetch_entity(char c, t_game *solong);
int			in_array(int val, int tab[], size_t siz);
#endif
