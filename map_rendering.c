/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:12:21 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 00:41:39 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_map(t_map *map, t_game *solong)
{
	t_entity	*entities[ENTITIES_TYPE_COUNT + 1];

	init_map_entities(map, entities, solong);
	solong->mlx = mlx_init();
	if (!solong->mlx)
		put_err("Failed to initialize MLX", solong, MLX_OFF);
	solong->win = mlx_new_window(solong->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
	if (!solong->win)
		put_err("Failed to initialize MLX", solong, MLX_OFF);
	solong->img.mlx_img = mlx_new_image(solong->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	solong->img.addr = mlx_get_data_addr(solong->img.mlx_img, &solong->img.bpp, &solong->img.line_len, &solong->img.endian);
}