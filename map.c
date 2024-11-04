/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:59:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/04 23:13:32 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// static int	check_map(t_map *map)
// {
// 	//map->exit.x = 0;
// 	//parsemap
// 	//check_errors
// 	//flood_fill
// 	return (0);
// }

static void	init_map_entities(t_map *map, t_entity *entities[], t_game *solong)
{	
	ft_putendl_fd("Loading images ..", 1);
	map->ground = ft_lstnew((t_entity){.xpm = XPM_GROUND});
	map->wall = ft_lstnew((t_entity){.xpm = XPM_WALL});
	map->exit = ft_lstnew((t_entity){.xpm = XPM_EXIT});
	map->player = ft_lstnew((t_entity){.xpm = XPM_PLAYER});
	map->collectible = ft_lstnew((t_entity){.xpm = XPM_COLLECTIBLE});
	map->adverse = ft_lstnew((t_entity){.xpm = XPM_ADVERSE});
	entities[0] = map->ground;
	entities[1] = map->wall;
	entities[2] = map->exit;
	entities[3] = map->player;
	entities[4] = map->collectible;
	entities[5] = map->adverse;
	entities[6] = NULL;
	while (*entities)
	{
		(*entities)->img = mlx_xpm_file_to_image(solong->mlx, (*entities)->xpm, 
		&((*entities)->imgwdth), &((*entities)->imghght));
		if (!(*entities)->xpm)
			put_err("Failled to generate mlx image from XPM file", solong, 1);
		(entities)++;
	}
	*(entities) -= ENTITIES_TYPE_COUNT;
}

//Parse grid
//Check Elements
//Map Integrity - Flood Fill

char	**create_grid(char *path, t_map *map, t_game *solong)
{
	int		fd;
	char	*row;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		put_err("Error opening file", solong, MLX_OFF);
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			return (close(fd), map->grid);
		else
		{
			printf("Grid ptr is %p && Currow idx is %ld\n", map->grid, map->col_size);
			map->grid = ft_realloc(map->grid, sizeof(char *) * (map->col_size + 2));
			if (!map->grid)
				put_err("Failed to realloc map grid", solong, MLX_OFF);
			map->grid[map->col_size] = row;
			ft_printf("Curr row address %p\n%s", map->grid[map->col_size], map->grid[map->col_size]);
			map->grid[++(map->col_size)] = NULL;
			ft_printf("Addr %p at index/row %d\n\n", map->grid[map->col_size - 1], map->col_size - 1);
		}
	}
}

// static void	parse_byte(char c, t_entity *elm_head, t_map *map)
// {
// 	t_entity	*elm;

// 	elm = elm_head;
// 	elm->count++;
	
// 	//else if (c == 'C' ||  c == 'A')
// 	if (!elm->first->img)
// 	{
// 		elm->first->img = mlx_xpm_file_to_image(solong->mlx, elm->first->xpm);
// 		if (!elm->first->img)
// 			put_err("Failled to generate image from XPM file");
// 	}
// 	return ;
// }

// static void	parse_grid(char **grid, t_game *solong)
// {
// 	size_t	row;
// 	size_t	col;

// 	row = 0;
// 	while (grid[row])
// 	{
// 		col = 0;
// 		while (grid[row][col] && grid[row][col] != '\n')
// 		{
// 			if (!ft_strchr(ALLOWED_ELEMS, grid[row][col]))
// 				put_err("Invalid tile / element", solong, MLX_OFF);
// 			else if (grid[row][col] == 'P')
			
// 			else if (grid[row][col] == 'C' || grid[row][col] == 'A')
// 				ft_lstadd_back(ft_lstnew());
// 			else if ()
// 				elm->pos = (t_point){.x = col, .y = row};
// 			col++;
// 		}
// 		row++;
// 	}

// 	// 	if (solong->map.row_size > 0 && (curr_rwsiz != solong->map.row_size))
// // 		put_err("Invalid map dimensions", solong, MLX_OFF);
// // 	else if (solong->map.row_size == 0)
// // 		solong->map.row_size = curr_rwsiz;
// }

int	parse_map(char *path, t_game *solong)
{
	solong->map = (t_map){.grid = NULL, .row_size = 0, .col_size = 0};
	init_map_entities(&(solong->map), solong->map.entities, solong);
	create_grid(path, &solong->map, solong);
	printf("Map grid is: %p\n", solong->map.grid);

	//parse_grid
	//flood_fill
	//check errors
	return (0);
}