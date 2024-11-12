/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:18:11 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/12 06:07:40 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_count	flood_fill(char **tab, t_point size, t_point cur)
{
	static t_count	count = {.collectible = 0, .exit = 0};

	if (cur.y < 0 || cur.y >= size.y
		|| cur.x < 0 || cur.x >= size.x
		|| tab[cur.y][cur.x] == 'F'
		|| tab[cur.y][cur.x] == '1'
		|| tab[cur.y][cur.x] == 'A')
		return ((t_count){});
	if (tab[cur.y][cur.x] == 'C')
		count.collectible++;
	else if (tab[cur.y][cur.x] == 'E')
		count.exit++;
	tab[cur.y][cur.x] = 'F';
	flood_fill(tab, size, (t_point){cur.x - 1, cur.y});
	flood_fill(tab, size, (t_point){cur.x + 1, cur.y});
	flood_fill(tab, size, (t_point){cur.x, cur.y - 1});
	flood_fill(tab, size, (t_point){cur.x, cur.y + 1});
	return (count);
}

static void	check_wall(char entity, t_point pos, t_game *solong)
{
	if (pos.x == 0 || pos.x == (int)solong->map.row_size - 1
		|| pos.y == 0 || pos.y == (int)solong->map.col_size - 1)
		if (entity != '1')
			put_err("Missing wall on map borders", solong);
	if (entity == 'E')
	{
		solong->map.exit_pos = (t_point){.x = pos.x, .y = pos.y};
		solong->map.count.exit++;
	}
	else if (entity == 'P')
	{
		solong->map.pchr_pos = (t_point){.x = pos.x, .y = pos.y};
		solong->map.count.player++;
	}
	else if (entity == 'C')
		solong->map.count.collectible++;
	else if (entity == 'A')
		solong->map.count.adverse++;
}

static void	parse_grid(char **grid, t_game *solong)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col] && grid[row][col] != '\n')
		{
			if (!ft_strchr(ALLOWED_ELEMS, grid[row][col]))
				put_err("Invalid tile / element", solong);
			check_wall(grid[row][col], (t_point){.x = col, .y = row}, solong);
			col++;
		}
		if (solong->map.row_size != col)
			put_err("Map : Inconsistent rows size", solong);
		solong->map.row_size = col;
		row++;
	}
	if (solong->map.count.player != 1 || solong->map.count.exit != 1
		|| solong->map.count.collectible < 1)
		put_err("Invalid entity count", solong);
}

char	**create_grid(char *path, t_map *map, t_game *solong)
{
	int		fd;
	char	*row;
	char	**grid;

	grid = NULL;
	solong->map.col_size = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		put_err(ERR_F_PATH_PERMS, solong);
	while (1)
	{
		row = get_next_line(fd);
		if (!row && !grid)
			put_err("Map file seems to be empty", solong);
		else if (!row && grid)
			return (close(fd), grid);
		grid = ft_realloc(grid, sizeof(char *) * (map->col_size + 2));
		if (!grid)
			(close(fd), put_err("Failled to realloc map grid", solong));
		grid[map->col_size] = row;
		grid[++(map->col_size)] = NULL;
	}
}

int	parse_map(char *path, t_game *solong)
{
	t_count	found_entities;

	solong->map = (t_map){.grid = NULL, .row_size = 0, .col_size = 0,};
	solong->map.grid = create_grid(path, &solong->map, solong);
	solong->map.row_size = ft_strlen(*(solong->map.grid)) - 1;
	parse_grid(solong->map.grid, solong);
	solong->map.shallow_grid = create_grid(path, &(solong->map), solong);
	found_entities = flood_fill(solong->map.shallow_grid,
			(t_point){.x = solong->map.row_size, .y = solong->map.col_size},
			solong->map.pchr_pos);
	if (solong->map.count.collectible != found_entities.collectible
		|| found_entities.exit != 1)
		put_err("Map : Unreachable exit or collectible", solong);
	else if ((solong->map.row_size + WIN_OFFST_INCOL) * TILE_SIZE > 1920
		|| (solong->map.col_size + CNTR_SIZ_INRW + WIN_OFFST_INRW)
		* TILE_SIZE > 1080)
		put_err("Map : Oversized dimensions", solong);
	ft_printf("%u collectibles, %u found\n",
		solong->map.count.collectible, found_entities.collectible);
	return (0);
}
