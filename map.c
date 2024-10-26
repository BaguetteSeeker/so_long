/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:59:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/26 14:06:07 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	*init_map(t_map *map)
{
	map->grid = NULL;
	map->row_size = 0;
	map->col_size = 0;
	map->size = 0;
	return (map);
}

static int	check_map(t_map *map)
{
	map->exit.x = 0;
	//parsemap
	//check_errors
	//flood_fill
	return (0);
}

static void	parse_elm(char c, size_t xpos, size_t ypos, t_map *map)
{
	map->size++;
	if (c == 'P')
	{
		map->player.x = xpos;
		map->player.y = ypos;
		map->count.player++;
	}
	else if (c == 'C')
	{
		map->collectible[map->count.collectibles].pos.x = xpos;
		map->collectible[map->count.collectibles].pos.y = ypos;
		map->count.collectibles++;
	}
	else if (c == 'E')
	{
		map->exit.x = xpos;
		map->exit.y = ypos;
		map->count.exit++;
	}
	else if (c == 'A')
	{	map->adverse[map->count.adverse].pos.x = xpos;
		map->adverse[map->count.adverse].pos.y = ypos;
		map->count.adverse++;
	}
	return ;
}

static void	parse_row(char *row, t_game *solong)
{
	size_t	curr_rwsiz;

	curr_rwsiz = 0;
	while (*row && *row != '\n')
	{
		curr_rwsiz++;
		if (!ft_strchr("01CEP", *row))
			put_err("Invalid tile / element", solong, MLX_OFF);
		else
			parse_elm(*row, curr_rwsiz, solong->map.col_size, &(solong->map));
		row++;
	}
	if (solong->map.row_size > 0 && (curr_rwsiz != solong->map.row_size))
		put_err("Invalid map dimensions", solong, MLX_OFF);
	else if (solong->map.row_size == 0)
		solong->map.row_size = curr_rwsiz;
	free(row - curr_rwsiz);
}

int	parse_map(char *path, t_game *solong)
{
	t_map	map;
	int		fd;
	char	*row;
	// size_t	i;
	// size_t	j;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (put_err("Error opening file", solong, MLX_OFF));
	init_map(&map);
	solong->map = map;
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
		{
			map.grid[map.col_size] = NULL;
			close(fd);
			return (check_map(&map));
		}
		else
		{
			map.grid = ft_realloc(map.grid, sizeof(char *) * (map.col_size + 1));
			//map.grid[map.col_size] = '\0';
			map.grid[map.col_size] = row;
			ft_printf("%s \n", map.grid[map.col_size]);
			parse_row(map.grid[map.col_size], solong);
			map.col_size++;
			//map.grid++;
			// while (map.grid)
			// {
			// 	gridcount++;
			// 	map.grid++;
			// }
			//ft_printf("Grid has %d rows\n", gridcount);
			//free(row);
		}
	}
}