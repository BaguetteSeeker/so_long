/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 12:33:48 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_err(char *msg, t_game *solong, int mlx_instance)
{
	int	i;

	i = 0;
	if (errno)
		perror(msg);
	else
		ft_putendl_fd(msg, 1);
	solong->map.grid = ft_clean_memtree(solong->map.grid);
	solong->map.shallow_grid = ft_clean_memtree(solong->map.shallow_grid);
	while (i < ENTITIES_TYPE_COUNT + 1)
	{
		if (solong->map.entities[i])
		{
			if (solong->map.entities[i]->img)
			{
				mlx_destroy_image(solong->mlx, solong->map.entities[i]->img);
				printf("Removing entity : %s\n", solong->map.entities[i]->xpm);
			}
			free(solong->map.entities[i]);
		}
		solong->map.entities[i] = NULL;
		i++;
	}
	if (mlx_instance == MLX_ON)
		destroy_mlx(solong);
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
	int	i;
	i = 0;
	while (i < ENTITIES_TYPE_COUNT)
	{
		printf("Entity : %s ", entities[i]->xpm);
		entities[i]->img = mlx_xpm_file_to_image(solong->mlx, entities[i]->xpm, 
		&(entities[i]->imgwdth), &(entities[i]->imghght));
		printf("Its ptr is : %p\n", entities[i]->img);
		if (!(entities[i]->img))
		{
			put_err("Failled to generate mlx image from XPM file", solong, MLX_ON);
		}
		i++;
	}
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
