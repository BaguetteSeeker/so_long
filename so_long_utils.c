/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 01:38:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/11 04:16:35 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	destroy_mlx(t_game *solong)
{
	ft_putendl_fd("Destroying mlx..\n", 1);
	if (solong->win)
	{
		mlx_clear_window(solong->mlx, solong->win);
		mlx_destroy_window(solong->mlx, solong->win);
	}
	if (solong->shape.img)
		mlx_destroy_image(solong->mlx, solong->shape.img);
	mlx_destroy_display(solong->mlx);
	free(solong->mlx);
	solong->mlx = NULL;
	return (0);
}

int	clean_game_memory(t_game *solong)
{
	int	i;

	i = 0;
	while (i < ENTITIES_TCOUNT + 1)
	{
		if (solong->map.entities[i])
		{
			if (solong->map.entities[i]->img)
				mlx_destroy_image(solong->mlx, solong->map.entities[i]->img);
			free(solong->map.entities[i]);
			solong->map.entities[i] = NULL;
		}
		i++;
	}
	solong->map.grid = ft_clean_memtree(solong->map.grid);
	solong->map.shallow_grid = ft_clean_memtree(solong->map.shallow_grid);
	if (solong->mlx_state)
		destroy_mlx(solong);
	return (0);
}

t_entity	*fetch_entity(char c, t_game *solong)
{
	int	pos;

	pos = 0;
	while (ALLOWED_ELEMS[pos] && ALLOWED_ELEMS[pos] != c)
		pos++;
	if (!ALLOWED_ELEMS[pos])
		put_err("Unknown entity within map boundaries", solong);
	return (solong->map.entities[pos]);
}

int	in_array(int val, int tab[], size_t siz)
{
	size_t	pos;

	pos = 0;
	while (pos != siz)
	{
		if (tab[pos] == val)
			return (pos);
		pos++;
	}
	return (-1);
}
