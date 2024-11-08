// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/21 22:59:00 by epinaud           #+#    #+#             */
// /*   Updated: 2024/11/07 18:04:14 by epinaud          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "so_long.h"
// // static int	check_map(t_map *map)
// // {
// // 	//map->exit.x = 0;
// // 	//parsemap
// // 	//check_errors
// // 	//flood_fill
// // 	return (0);
// // }

// static void	init_map_entities(t_map *map, t_entity *entities[])
// {	
// 	ft_putendl_fd("Loading entities ..", 1);
// 	map->ground = ft_lstnew(&(t_entity){.xpm = XPM_GROUND, .count = 0});
// 	map->wall = ft_lstnew(&(t_entity){.xpm = XPM_WALL, .count = 0});
// 	map->exit = ft_lstnew(&(t_entity){.xpm = XPM_EXIT, .count = 0});
// 	map->player = ft_lstnew(&(t_entity){.xpm = XPM_PLAYER, .count = 0});
// 	map->collectible = ft_lstnew(&(t_entity){.xpm = XPM_COLLECTIBLE, .count = 0});
// 	map->adverse = ft_lstnew(&(t_entity){.xpm = XPM_ADVERSE, .count = 0});
// 	entities[0] = map->ground;
// 	entities[1] = map->wall;
// 	entities[2] = map->exit;
// 	entities[3] = map->player;
// 	entities[4] = map->collectible;
// 	entities[5] = map->adverse;
// 	entities[6] = NULL;
// 	ft_strlcpy(map->valid_entities, ALLOWED_ELEMS, ENTITIES_TYPE_COUNT);
// 	printf("Test entities, shud display player xpm path : %s\n", entities[3]->xpm);
// 	// while (*entities)
// 	// {
// 	// 	printf("Entity : %s\n", (*entities)->xpm);
// 	// 	(*entities)->img = mlx_xpm_file_to_image(solong->mlx, (*entities)->xpm, 
// 	// 	&((*entities)->imgwdth), &((*entities)->imghght));
// 	// 	if (!((*entities)->xpm))
// 	// 		put_err("Failled to generate mlx image from XPM file", solong);
// 	// 	entities++;
// 	// }
// 	// entities -= ENTITIES_TYPE_COUNT;
// }

// //Parse grid
// //Check Elements
// //Map Integrity - Flood Fill

// char	**create_grid(char *path, t_map *map, t_game *solong)
// {
// 	int		fd;
// 	char	*row;
// 	int		prev_rowsiz;

// 	prev_rowsiz = -1;
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		put_err("Error opening file", solong);
// 	printf("Creating grid .. File path is %s\n Fd is %d\n", path, fd);
// 	while (1)
// 	{
// 		row = get_next_line(fd);
// 		if (!row)
// 			return (close(fd), map->grid);
// 		map->row_size = ft_strlen(row);
// 		if (prev_rowsiz > -1 && (size_t)prev_rowsiz != map->row_size)
// 			put_err("Map : Inconsistent rows size", solong);
// 		else
// 		{
// 			map->grid = ft_realloc(map->grid, sizeof(char *) * (map->col_size + 2));
// 			if (!map->grid)
// 				put_err("Failed to realloc map grid", solong);
// 			map->grid[map->col_size] = row;
// 			map->grid[++(map->col_size)] = NULL;
// 			ft_printf("Curr row address %p\n%s", map->grid[map->col_size - 1], map->grid[map->col_size - 1]);
// 		}
// 		prev_rowsiz = map->row_size;
// 	}
// }

// static void	parse_grid(char **grid, t_entity *entities[], t_game *solong)
// {
// 	size_t	row;
// 	size_t	col;
// 	t_entity	*elem;

// 	row = 0;
// 	ft_putendl_fd(grid[row], 1);
// 	while (grid[row])
// 	{
// 		col = 0;
// 		while (grid[row][col] && grid[row][col] != '\n')
// 		{
// 			if (!ft_strchr(ALLOWED_ELEMS, grid[row][col]))
// 				put_err("Invalid tile / element", solong);
// 			else
// 				elem = entities[(size_t)(ft_strchr(solong->map.valid_entities, grid[row][col]) - solong->map.valid_entities[0])];
// 			if (ft_strchr("PE", grid[row][col]))
// 				elem->pos = (t_point){.x = col, .y = row};
// 			else if (ft_strchr("CA", grid[row][col]))
// 				ft_lstadd_back(&elem, ft_lstnew(&(t_entity){.count = elem->count + 1,
// 					.next = NULL, .pos = (t_point){.x = col, .y = row}}));
// 			elem->count++;
// 			col++;
// 		}
// 		row++;
// 	}
// 	//solong->map.grid_size = col * row; 
// }

// int	parse_map(char *path, t_game *solong)
// {	
// 	solong->map = (t_map){.grid = NULL, .row_size = 0, .col_size = 0, 
// 	.ground = 0, .wall = 0, .player = 0, .exit = 0, 
// 	.adverse = 0, .collectible = 0};
// 	init_map_entities(&(solong->map), solong->map.entities);
// 	create_grid(path, &solong->map, solong);
// 	printf("Map grid is: %p\n", solong->map.grid);
// 	parse_grid(solong->map.grid, solong->map.entities, solong);
// 	if (solong->map.player->count != 1 || solong->map.exit->count != 1 || solong->map.collectible->count < 1)
// 		put_err("Invalid entity count", solong);
// 	//flood_fill
// 	//flood_fill(solong->map.grid, solong->map.grid_size, solong->map.player->pos);
// 	//check errors
// 	return (0);
// }