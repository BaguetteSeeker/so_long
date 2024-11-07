/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:18:11 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 00:10:28 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_count	flood_fill(char **tab, t_point size, t_point cur)
{
	static t_count	count = {.collectible = 0, .exit = 0};

	if (cur.y < 0 || cur.y >= size.y
		|| cur.x < 0 || cur.x >= size.x
		|| tab[cur.y][cur.x] == 'F'
		|| tab[cur.y][cur.x] == '1')
		return ((t_count){});
	if (tab[cur.y][cur.x] == 'C')
		count.collectible++;
	else if (tab[cur.y][cur.x] == 'E')
		count.exit++;
	printf("Flooding %d X and %d Y Elm is %c && %ld clts\n", cur.x, cur.y, tab[cur.y][cur.x], count.collectible);
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
			put_err("Missing wall on map borders", solong, MLX_OFF);
	if (entity == 'E')
		solong->map.count.exit++;
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
				put_err("Invalid tile / element", solong, MLX_OFF);
			check_wall(grid[row][col], (t_point){.x = col, .y = row}, solong);
			col++;
		}
		if (solong->map.row_size != col)
			put_err("Map : Inconsistent rows size", solong, MLX_OFF);
		solong->map.row_size = col;
		row++;
	}
	if (solong->map.count.player != 1 || solong->map.count.exit != 1
		|| solong->map.count.collectible < 1)
		put_err("Invalid entity count", solong, MLX_OFF);
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
		put_err("Error opening file", solong, MLX_OFF);
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			return (close(fd), grid);
		else
		{
			grid = ft_realloc(grid, sizeof(char *) * (map->col_size + 2));
			if (!grid)
				put_err("Failed to realloc map grid", solong, MLX_OFF);
			grid[map->col_size] = row;
			grid[++(map->col_size)] = NULL;
		}
	}
}

int	parse_map(char *path, t_game *solong)
{
	t_count	found_entities;

	solong->map = (t_map){.grid = NULL, .row_size = 0, .col_size = 0,
		.ground = 0, .wall = 0, .player = 0, .exit = 0,
		.adverse = 0, .collectible = 0};
	solong->map.grid = create_grid(path, &solong->map, solong);
	solong->map.row_size = ft_strlen(*(solong->map.grid)) - 1;
	parse_grid(solong->map.grid, solong);
	solong->map.shallow_grid = create_grid(path, &(solong->map), solong);
	found_entities = flood_fill(solong->map.shallow_grid,
			(t_point){.x = solong->map.row_size, .y = solong->map.col_size},
			solong->map.pchr_pos);
	if (solong->map.count.collectible != found_entities.collectible
		|| found_entities.exit != 1)
		put_err("Map : Unreachable exit or collectible", solong, MLX_OFF);
	printf("%ld collectibles, %ld found\n", solong->map.count.collectible, found_entities.collectible);
	return (0);
}
