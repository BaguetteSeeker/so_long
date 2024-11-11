/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:12:21 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/11 03:34:15 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_xpms(t_entity *entities[], t_game *solong)
{
	t_entity	new_entity;
	char		**xpm_lst;
	int			entt_id;
	int			i;

	xpm_lst = XPM_LST;
	i = 0;
	while (i < ENTITIES_TCOUNT)
	{
		entt_id = ENTITIES_ID[i++];
		new_entity = (t_entity){.img = NULL, .imghght = 0, .imgwdth = 0};
		ft_strlcpy(new_entity.xpm, xpm_lst[entt_id],
			ft_strlen(xpm_lst[entt_id]) + 1);
		entities[entt_id] = ft_lstnew(&new_entity);
		entities[entt_id]->img = mlx_xpm_file_to_image(solong->mlx,
				entities[entt_id]->xpm, &(entities[entt_id]->imgwdth),
				&(entities[entt_id]->imghght));
		if (!(entities[entt_id]->img))
			put_err("Failled to generate mlx image from XPM file", solong);
	}
	entities[10] = NULL;
}

void	render_tile(size_t xpm_id, t_point pos, t_game *solong)
{
	mlx_put_image_to_window(solong->mlx, solong->win,
		solong->map.entities[xpm_id]->img,
		pos.x * TILE_SIZE,
		pos.y * TILE_SIZE);
}

void	render_steps_count(size_t steps, t_game *solong)
{
	static char	steps_msg[255];
	char		*stred_steps;
	t_point		pos;

	pos = (t_point){solong->map.row_size * (TILE_SIZE - 3) / 2,
	(solong->map.col_size  * TILE_SIZE) + (TILE_SIZE / 2)};
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
	load_xpms(solong->map.entities, solong);
	render_initial_map(solong->map.grid, solong);
}
