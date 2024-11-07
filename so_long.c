/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 00:39:24 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_err(char *msg, t_game *solong, int mlx_instance)
{
	if (errno)
		perror(msg);
	else
		ft_putendl_fd(msg, 1);
	if (mlx_instance == MLX_ON)
		destroy_mlx(solong);
	solong->map.grid = ft_clean_memtree(solong->map.grid);
	solong->map.shallow_grid = ft_clean_memtree(solong->map.shallow_grid);
	while (ENTITIES_TYPE_COUNT >= 0)
	{
		if (solong->map.entities[ENTITIES_TYPE_COUNT])
			free(solong->map.entities[ENTITIES_TYPE_COUNT]);
		solong->map.entities[ENTITIES_TYPE_COUNT] = NULL;
	}
	exit(EXIT_FAILLURE);
}

void	init_map_entities(t_map *map, t_entity *entities[], t_game *solong)
{	
	ft_putendl_fd("Loading entities ..", 1);
	map->ground = ft_lstnew(&(t_entity){.xpm = XPM_GROUND, .count = 0});
	map->wall = ft_lstnew(&(t_entity){.xpm = XPM_WALL, .count = 0});
	map->exit = ft_lstnew(&(t_entity){.xpm = XPM_EXIT, .count = 0});
	map->player = ft_lstnew(&(t_entity){.xpm = XPM_PLAYER, .count = 0});
	map->collectible = ft_lstnew(&(t_entity){.xpm = XPM_COLLECTIBLE, .count = 0});
	map->adverse = ft_lstnew(&(t_entity){.xpm = XPM_ADVERSE, .count = 0});
	entities[0] = map->ground;
	entities[1] = map->wall;
	entities[2] = map->exit;
	entities[3] = map->player;
	entities[4] = map->collectible;
	entities[5] = map->adverse;
	entities[6] = NULL;
	ft_strlcpy(map->valid_entities, ALLOWED_ELEMS, ENTITIES_TYPE_COUNT);
	printf("Test entities, shud display player xpm path : %s\n", entities[3]->xpm);
	while (*entities)
	{
		printf("Entity : %s\n", (*entities)->xpm);
		(*entities)->img = mlx_xpm_file_to_image(solong->mlx, (*entities)->xpm, 
		&((*entities)->imgwdth), &((*entities)->imghght));
		if (!((*entities)->xpm))
			put_err("Failled to generate mlx image from XPM file", solong, MLX_OFF);
		entities++;
	}
	entities -= ENTITIES_TYPE_COUNT;
}

//void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);

//Map parsing
//Rendering
//Events Management
//Error Handling
int	main(int argc, char *argv[])
{
	t_game	solong;

	if (argc < 2)
	   	put_err("Missing map (./maps/<map>.ber)", &solong, MLX_OFF);
	if (argc > 2)
	    put_err("Too many arguments", &solong, MLX_OFF);
	if (parse_map(argv[1], &solong))
		put_err("Failled to parse map", &solong, MLX_OFF);
	put_map(&solong.map, &solong);
	setup_hooks(&solong);	
	//enable actions
	exit(0);
}
