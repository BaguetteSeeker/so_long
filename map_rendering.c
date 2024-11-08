/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:12:21 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 15:54:19 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_entity	*fetch_entity(char c, t_game *solong)
{
	int	pos;

	pos = 0;
	while (ALLOWED_ELEMS[pos] && ALLOWED_ELEMS[pos] != c)
		pos++;
	if (!ALLOWED_ELEMS[pos])
		return (NULL);
	return (solong->map.entities[pos]);
}

static void put_entities(char **grid, t_game *solong)
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
			fetch_entity(grid[row][col], solong)->img,
			col * TILE_SIZE, row * TILE_SIZE);
			col++;
		}

		row++;
	}
}

static void put_grass(char **grid, t_game *solong)
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
			col++;
		}

		row++;
	}
}

void	put_map(t_map *map, t_game *solong)
{
	//t_entity	*entities[ENTITIES_TYPE_COUNT + 1];
	// (void)map;
	// (void)entities;
	solong->mlx = mlx_init();
	if (!solong->mlx)
		put_err("Failed to initialize MLX", solong, MLX_ON);
	solong->win = mlx_new_window(solong->mlx, map->row_size * TILE_SIZE, (map->col_size + 2) * TILE_SIZE, GAME_NAME);
	if (!solong->win)
		put_err("Failed to initialize MLX", solong, MLX_ON);
	solong->img.mlx_img = mlx_new_image(solong->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	solong->img.addr = mlx_get_data_addr(solong->img.mlx_img, &solong->img.bpp, &solong->img.line_len, &solong->img.endian);
	init_map_entities(map, solong->map.entities, solong);
	//mlx_put_image_to_window(solong->mlx, solong->win, solong->map.entities[1]->img, 500, 500);
	put_grass(solong->map.grid, solong);
	put_entities(solong->map.grid, solong);
	// while (solong->map.entities)
	// 	mlx_put_image_to_window(solong->mlx, solong->img.mlx_img, (*solong->map.entities)++, 32, 32);
	// solong->map.entities -= ENTITIES_TYPE_COUNT;
}