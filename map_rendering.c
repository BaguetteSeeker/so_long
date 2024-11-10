/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:12:21 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/10 17:02:54 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_point cur, t_game *solong)
{
	mlx_put_image_to_window(solong->mlx, solong->win,
		solong->map.entities[TILE_ID]->img,
		cur.x * TILE_SIZE,
		cur.y * TILE_SIZE);
}

void	render_entity(int entity_id, t_point cur, t_game *solong)
{
	mlx_put_image_to_window(solong->mlx, solong->win,
		solong->map.entities[entity_id]->img,
		cur.x * TILE_SIZE,
		cur.y * TILE_SIZE);
}

void	render_exit(size_t exit_status, t_game *solong)
{
	size_t	exit_id;
	
	if (EXIT_OPEN_ID == exit_status)
		exit_id = EXIT_OPEN_ID;
	else
		exit_id = EXIT_SHUT_ID;
	mlx_put_image_to_window(solong->mlx, solong->win, 
		solong->map.entities[exit_id]->img, 
		solong->map.exit_pos.x * TILE_SIZE,
		solong->map.exit_pos.y  * TILE_SIZE);
}

void	render_steps_count(size_t steps, t_game *solong)
{
	static char	steps_msg[255];
	char		*stred_steps;
	t_point		pos;

	pos = (t_point){solong->map.row_size * (TILE_SIZE - 3) / 2,
	(solong->map.col_size  * (TILE_SIZE + CNTR_SIZ_INRW)) + (TILE_SIZE / 4)};
	stred_steps = ft_itoa(steps);
	ft_bzero(steps_msg, 255);
	ft_strlcpy(steps_msg, "You walked ", 12);
	ft_strlcpy(&steps_msg[11], stred_steps, ft_strlen(stred_steps) + 1);
	ft_strlcat(&steps_msg[ft_strlen(steps_msg)], " tiles !", 9);
	mlx_put_image_to_window(solong->mlx, solong->win, solong->shape.img, 0,
			TILE_SIZE * solong->map.col_size);
	mlx_string_put(solong->mlx, solong->win, pos.x, pos.y, 0XFFFFFF, steps_msg);
	free(stred_steps);
}

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
			(map->col_size + CNTR_SIZ_INRW) * TILE_SIZE, GAME_NAME);
	if (!solong->win)
		put_err("Failed to initialize MLX", solong);
	solong->shape.img = mlx_new_image(solong->mlx,
			solong->map.row_size * TILE_SIZE, TILE_SIZE);
	render_rect(&solong->shape, (t_rect){0, solong->map.col_size * TILE_SIZE,
		0, 0, COUNTER_BGCLR});
	solong->shape.addr = mlx_get_data_addr(solong->shape.img,
			&solong->shape.bpp, &solong->shape.line_len, &solong->shape.endian);
	init_map_entities(map, solong->map.entities, solong);
	render_initial_map(solong->map.grid, solong);
}
