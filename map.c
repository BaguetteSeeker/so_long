/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:59:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/30 12:42:11 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static t_map	*init_map(t_map *map)
// {
// 	map->grid = NULL;
// 	map->row_size = 0;
// 	map->col_size = 0;
// 	return (map);
// }

// static int	check_map(t_map *map)
// {
// 	//map->exit.x = 0;
// 	//parsemap
// 	//check_errors
// 	//flood_fill
// 	return (0);
// }

// static void	load_map(t_game *solong, t_map *map)
// {
// 	t_element	*elm_arr;

	
// 	ft_putendl_fd("Images loading ..", 1);

// 	map->ground.xpm = XPM_GROUND;
// 	map->wall.xpm = XPM_WALL;
// 	map->exit.xpm = XPM_EXIT;
// 	map->collectible.xpm = XPM_COLLECTIBLE;
// 	map->player.xpm = XPM_PLAYER;
// 	map->adverse.xpm = XPM_ADVERSE;

// 	while (*elm_arr)
// 	{
// 		map->elm.img = mlx_xpm_file_to_image(solong, map->elm.xpm,);
// 		if (!map->elm.img)
// 			put_err("Failled convert XPM into file_image", solong, 1);
// 	}
// 	map->ground.img = mlx_xpm_file_to_image(solong, map->ground.xpm,);
// 	map->wall.xpm = XPM_WALL;
// 	map->exit.xpm = XPM_EXIT;
// 	map->collectible.xpm = XPM_COLLECTIBLE;
// 	map->player.xpm = XPM_PLAYER;
// 	map->adverse.xpm = XPM_ADVERSE;

// }

// static void	parse_elm(char c, size_t xpos, size_t ypos, t_map *map)
// {
// 	map->size++;
// 	if (c == 'P')
// 	{
// 		map->player = (t_point){.x = xpos, .y = ypos};
// 		map->count.player++;
// 	}
// 	else if (c == 'C')
// 	{
// 		//printf("Pointer is %p\n", map->collectible);
// 		*(map->collectible)->pos = (t_point){.x = xpos, .y = ypos};
// 		map->count.collectibles++;
// 	}
// 	else if (c == 'E')
// 	{
// 		map->exit = (t_point){.x = xpos, .y = ypos};
// 		map->count.exit++;
// 	}
// 	else if (c == 'A')
// 	{	
// 		*(map->adverse)->pos = (t_point){.x = xpos, .y = ypos};
// 		map->count.adverse++;
// 	}
// 	return ;
// }

// static void	parse_row(char *row, t_game *solong)
// {
// 	size_t	curr_rwsiz;

// 	curr_rwsiz = 0;
// 	while (*row && *row != '\n')
// 	{
// 		curr_rwsiz++;
// 		if (!ft_strchr("01CEP", *row))
// 			put_err("Invalid tile / element", solong, MLX_OFF);
// 		else
// 			parse_elm(*row, curr_rwsiz, solong->map.col_size, &(solong->map));
// 		row++;
// 	}
// 	if (solong->map.row_size > 0 && (curr_rwsiz != solong->map.row_size))
// 		put_err("Invalid map dimensions", solong, MLX_OFF);
// 	else if (solong->map.row_size == 0)
// 		solong->map.row_size = curr_rwsiz;
// 	free(row - curr_rwsiz);
// }

//Create & fill grid
//Parse grid
//Check Elements
//Map Integrity - Flood Fill
char	**create_grid(char *path, t_map *map, t_game *solong)
{
	int		fd;
	// char	*row;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		put_err("Error opening file", solong, MLX_OFF);
	while (1)
	{
		//row = get_next_line(fd);
		if (1)
		{
			// if (map->col_size)
			// 	map->grid[map->col_size] = NULL;
			return (close(fd), map->grid);
		}
		else
		{
			printf("%ld\n", map->col_size);
			//map->grid = ft_realloc(map->grid, sizeof(char *) * (map->col_size + 2));
			//map->grid[map->col_size] = row;
			//ft_printf("%s \n", map->grid[map->col_size]);
			//parse_row(map->grid[map->col_size], solong);
			map->col_size++;
			//ft_printf("Grid has %d rows\n", gridcount);
		}
	}
}

int	parse_map(char *path, t_game *solong)
{
	t_map	map;

	map = (t_map){.grid = NULL, .row_size = 0, .col_size = 0};
	solong->map = &map;
	create_grid(path, &map, solong);
	//parse_grid
	return (0);
}