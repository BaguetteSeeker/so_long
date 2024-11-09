/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:12:21 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/09 03:42:02 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void	render_player_move(t_point new_pos, t_game *solong)
// {
// 	mlx_put_image_to_window(solong->mlx, solong->win,
// 			fetch_entity('0', solong)->img,
// 			new_pos.x * TILE_SIZE, new_pos.y * TILE_SIZE);
	//Update char on map
// }

static void	render_initial_map(char **grid, t_game *solong)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col] && grid[row][col] != '\n')
		{
			mlx_put_image_to_window(solong->mlx, solong->win,
				fetch_entity('0', solong)->img,
				col * TILE_SIZE, row * TILE_SIZE);
			if (grid[row][col] != '0')
				mlx_put_image_to_window(solong->mlx, solong->win,
					fetch_entity(grid[row][col], solong)->img,
					col * TILE_SIZE, row * TILE_SIZE);
			col++;
		}
		row++;
	}
}

void	put_map(t_map *map, t_game *solong)
{
	solong->mlx = mlx_init();
	if (!solong->mlx)
		put_err("Failed to initialize MLX", solong);
	solong->mlx_state = 1;
	solong->win = mlx_new_window(solong->mlx, map->row_size * TILE_SIZE,
			(map->col_size + 1) * TILE_SIZE, GAME_NAME);
	if (!solong->win)
		put_err("Failed to initialize MLX", solong);
	solong->shape.img = mlx_new_image(solong->mlx,
			solong->map.row_size * TILE_SIZE, TILE_SIZE);
	render_rect(&solong->shape, (t_rect){0, solong->map.col_size * TILE_SIZE,
		0, 0, RECT1_COLR});
	solong->shape.addr = mlx_get_data_addr(solong->shape.img,
			&solong->shape.bpp, &solong->shape.line_len, &solong->shape.endian);
	init_map_entities(map, solong->map.entities, solong);
	render_initial_map(solong->map.grid, solong);
}
