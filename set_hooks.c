/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:45:08 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/09 03:35:34 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_steps_count(size_t steps, t_game *solong)
{
	static char	steps_msg[255];
	char		*stred_steps;
	t_point		pos;

	pos = (t_point){solong->map.row_size * (TILE_SIZE - 3) / 2, (solong->map.col_size + 1) * (TILE_SIZE - 2)};
	stred_steps = ft_itoa(steps);
	ft_bzero(steps_msg, 255);
	ft_strlcpy(steps_msg, "You walked ", 12);
	ft_strlcpy(&steps_msg[11], stred_steps, ft_strlen(stred_steps) + 1);
	ft_strlcat(&steps_msg[ft_strlen(steps_msg)], " tiles !", 7);
	mlx_put_image_to_window(solong->mlx, solong->win, solong->shape.img, 0, TILE_SIZE * solong->map.col_size);
	mlx_string_put(solong->mlx, solong->win, pos.x, pos.y, 0XFFFFFF, steps_msg);
	free(stred_steps);
}

static void	move_player(int key_symbol, t_game *solong)
{
	t_point			next_pos;
	t_point			curr_pos;
	static size_t	steps = 0;
	static size_t	items = 0;

	steps++;
	render_steps_count(steps, solong);
	ft_printf("You walked : %u tiles\n", steps);
		curr_pos = solong->map.pchr_pos;
	next_pos = curr_pos;
	if (key_symbol == XK_Right || key_symbol == XK_d)
		next_pos.x += 1;
	else if (key_symbol == XK_Left || key_symbol == XK_a)
		next_pos.x -= 1;
	else if (key_symbol == XK_Up || key_symbol == XK_w)
		next_pos.y -= 1;
	else if (key_symbol == XK_Down || key_symbol == XK_s)
		next_pos.y += 1;

	if (solong->map.grid[next_pos.y][next_pos.x] == '1')
		return (ft_putendl_fd("You just hit a wall !", 1));
	else if (solong->map.grid[next_pos.y][next_pos.x] == 'A')
	{
		ft_putendl_fd("You just hit an ennemy !\n\nGAME OVER", 1);
		close_game(solong);
		return (ft_putendl_fd("You just hit an ennemy !", 1));
	}
	else if (solong->map.grid[next_pos.y][next_pos.x] == 'C')
	{
		items++;
		//Move char
		if (items == solong->map.count.collectible)
			//open portal
		return (ft_putendl_fd("You got a new collectible !", 1));
	}
	else if (solong->map.grid[next_pos.y][next_pos.x] == 'E')
	{
		//Move char
		if (items == solong->map.count.collectible)
			ft_putendl_fd("Congratz, you just won the game !", 1);
		return (ft_putendl_fd("You walked over the exit !", 1));
	}
	else if (solong->map.grid[next_pos.y][next_pos.x] == '0')
		return (ft_putendl_fd("You walked over some grass !", 1));
	else if (solong->map.grid[next_pos.y][next_pos.x] == 'P')
		return (ft_putendl_fd("You just walked over yourself.. Wait, what !?", 1));
	//clean curr pos
	//draw nextpos
	//update pchar_pos	
}

int	on_keypress(int key_symbol, t_game *solong)
{
	if (key_symbol == XK_Escape)
		exit(close_game(solong));
	else if (in_array(key_symbol, MOV_KEYS, sizeof(MOV_KEYS)) != -1)
		move_player(key_symbol, solong);
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