/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:45:08 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/10 05:42:16 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_move(t_point cur, t_point nxt, char *track_path, t_game *solong)
{
	(void)track_path;
	render_tile(nxt, solong);
	render_tile(cur, solong);
	//render player
	// mlx_put_image_to_window(solong->mlx, solong->win, 
	// 	solong->map.entities[fetch_entity(track_path[NXT_POS])]->img, nxt.x * TILE_SIZE, nxt.y * TILE_SIZE);

	render_exit(EXIT_SHUT_ID, solong);
	//player_getrot
	render_entity(CHAR_FRT_ID, nxt, solong);
// 	if (track_path[NXT_POS] == '0')
// 		return (ft_putendl_fd("You walked over some grass !", 1));
}

static t_point	set_player_angle(int keysym, t_point nxt_pos, size_t *cardinal)
{
	if (keysym == XK_Right || keysym == XK_d)
	{
		*cardinal = CHAR_RGT_ID;
		nxt_pos.x += 1;
	}
	else if (keysym == XK_Left || keysym == XK_a)
	{
		*cardinal = CHAR_LFT_ID;
		nxt_pos.x -= 1;
	}
	else if (keysym == XK_Up || keysym == XK_w)
	{
		*cardinal = CHAR_BCK_ID;
		nxt_pos.y -= 1;
	}
	else if (keysym == XK_Down || keysym == XK_s)
	{
		*cardinal = CHAR_FRT_ID;
		nxt_pos.y += 1;
	}
	return (nxt_pos);
}

static void	keymove_handler(int key_symbol, t_point *cur_pos, t_game *solong)
{
	t_point			next_pos;
	static size_t	steps = 0;
	static size_t	items = 0;
	size_t			pchar_cardinal;
	static char		track_path[3] = "   ";

	track_path[CUR_POS] = solong->map.grid[cur_pos->y][cur_pos->x];
	next_pos = set_player_angle(key_symbol, *cur_pos, &pchar_cardinal);
	track_path[NXT_POS] = solong->map.grid[next_pos.y][next_pos.x];

	if (track_path[NXT_POS] == '1')
		return (ft_putendl_fd("You just hit a wall !", 1));
	render_steps_count(++steps, solong);
	ft_printf("You walked : %u tiles\n", steps);
	render_move(*cur_pos, next_pos, track_path, solong);
	if (track_path[NXT_POS] == 'A')
		close_game("You just hit an ennemy !\n\nGAME OVER", solong);
	else if (track_path[NXT_POS] == 'C')
	{
		if (++items == solong->map.count.collectible)
		{
			ft_putendl_fd("Got all collectible bud, run to the EXIT!", 1);
			render_exit(EXIT_OPEN_ID, solong);
		}
	}
	else if (track_path[NXT_POS] == 'E' && items == solong->map.count.collectible)
		close_game("Congratz, you just won the game !", solong);	
	//update pchar_pos on map
	track_path[PRV_POS] = solong->map.grid[cur_pos->y][cur_pos->x];
	*cur_pos = next_pos;
}

int	on_keypress(int key_symbol, t_game *solong)
{
	if (key_symbol == XK_Escape)
		exit(close_game("", solong));
	else if (in_array(key_symbol, MOV_KEYS, sizeof(MOV_KEYS)) != -1)
		keymove_handler(key_symbol, &(solong->map.pchr_pos), solong);
	return (0);
}

void    setup_hooks(t_game *solong)
{
	ft_putendl_fd("Setting up hooks\n", 1);
	mlx_loop_hook(solong->mlx, &render_loop, solong);
	mlx_hook(solong->win, KeyRelease, KeyReleaseMask, &on_keypress, solong);
	mlx_hook(solong->win, DestroyNotify, StructureNotifyMask, &close_game, solong);
	mlx_loop(solong->mlx);
}