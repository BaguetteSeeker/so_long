/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:37:01 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/11 06:05:08 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_player(t_point pos, size_t cardinal, t_game *solong)
{
	render_tile(TILE_ID, pos, solong);
	render_tile(cardinal, pos, solong);
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

static void	interact_entity(char nxt_entt, t_game *solong)
{
	static size_t	items = 0;
	static size_t	exit_hit = 0;

	if (exit_hit)
	{
		render_tile(EXIT_SHUT_ID, solong->map.exit_pos, solong);
		exit_hit = 0;
	}
	if (nxt_entt == 'A')
		close_game("You just hit an ennemy !\n\nGAME OVER", solong);
	else if (nxt_entt == 'C')
	{
		if (++items == solong->map.count.collectible)
		{
			ft_putendl_fd("Got all collectibles bud, run to the EXIT!", 1);
			render_tile(EXIT_OPEN_ID, solong->map.exit_pos, solong);
		}
	}
	else if (nxt_entt == 'E')
	{
		exit_hit++;
		if (items == solong->map.count.collectible)
			close_game("Congratz, you just won the game !", solong);
	}
}

void	move_player(int keysym, t_point *curpos, t_game *solong)
{
	t_point			nxt_pos;
	char			nxt_entt;
	static size_t	steps = 0;
	size_t			orientation;

	nxt_pos = set_player_angle(keysym, *curpos, &orientation);
	nxt_entt = solong->map.grid[nxt_pos.y][nxt_pos.x];
	render_player(*curpos, orientation, solong);
	if (nxt_entt == '1')
		return (ft_putendl_fd("You just hit a wall !", 1));
	render_steps_count(++steps, solong);
	ft_printf("You walked : %u tiles\n", steps);
	render_tile(TILE_ID, *curpos, solong);
	if (curpos->y != solong->map.exit_pos.y
		|| curpos->x != solong->map.exit_pos.x)
		solong->map.grid[curpos->y][curpos->x] = '0';
	if (nxt_entt != 'E')
		solong->map.grid[nxt_pos.y][nxt_pos.x] = 'P';
	render_tile(orientation, nxt_pos, solong);
	interact_entity(nxt_entt, solong);
	*curpos = nxt_pos;
}
