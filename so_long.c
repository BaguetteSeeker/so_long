/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 23:26:01 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int destroy_mlx(t_game *solong)
{
    ft_putendl_fd("Destroying mlx..\n", 1);
	if (solong->win)
	{
		mlx_clear_window(solong->mlx, solong->win);
		mlx_destroy_window(solong->mlx, solong->win);
	}
	if (solong->img.mlx_img)
		mlx_destroy_image(solong->mlx, solong->img.mlx_img);
	mlx_destroy_display(solong->mlx);
	free(solong->mlx);
	solong->mlx = NULL;
	return (0);
}

int	clean_game_memory(t_game *solong)
{
	int	i;

	i = 0;
	while (i < ENTITIES_TYPE_COUNT + 1)
	{
		if (solong->map.entities[i])
		{
			if (solong->map.entities[i]->img)
			{
				mlx_destroy_image(solong->mlx, solong->map.entities[i]->img);
				ft_printf("Removing entity : %s\n", solong->map.entities[i]->xpm);
			}
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

int	close_game(t_game *solong)
{
	clean_game_memory(solong);

	ft_putendl_fd("Closing game..\n\n..\n", 1);
	exit(0);
}

int	put_err(char *msg, t_game *solong)
{
	if (errno)
		perror(msg);
	else
		ft_putendl_fd(msg, 1);
	clean_game_memory(solong);
	exit(EXIT_FAILLURE);
}

void	init_map_entities(t_map *map, t_entity *entities[], t_game *solong)
{	
	int	i;
	
	i = 0;
	ft_putendl_fd("Loading entities ..", 1);
	entities[TILE_ID] = ft_lstnew(&(t_entity){.xpm = XPM_GROUND});
	entities[WALL_ID] = ft_lstnew(&(t_entity){.xpm = XPM_WALL});
	entities[EXIT_SHUT_ID] = ft_lstnew(&(t_entity){.xpm = XPM_EXIT_CLOSED});
	entities[EXIT_OPEN_ID] = ft_lstnew(&(t_entity){.xpm = XPM_EXIT_OPEN});
	entities[CHAR_RGT_ID] = ft_lstnew(&(t_entity){.xpm = XPM_PLAYER_RIGHT});
	entities[CHAR_LFT_ID] = ft_lstnew(&(t_entity){.xpm = XPM_PLAYER_LEFT});
	entities[CHAR_BCK_ID] = ft_lstnew(&(t_entity){.xpm = XPM_PLAYER_BACK});
	entities[CHAR_FRT_ID] = ft_lstnew(&(t_entity){.xpm = XPM_PLAYER_FRONT});
	entities[CLCTBL_ID] = ft_lstnew(&(t_entity){.xpm = XPM_COLLECTIBLE});
	entities[ADVERSE_ID] = ft_lstnew(&(t_entity){.xpm = XPM_ADVERSE});
	entities[10] = NULL;
	ft_strlcpy(map->valid_entities, ALLOWED_ELEMS, ENTITIES_TYPE_COUNT);
	while (i < ENTITIES_TYPE_COUNT)
	{
		entities[i]->img = mlx_xpm_file_to_image(solong->mlx, entities[i]->xpm, 
		&(entities[i]->imgwdth), &(entities[i]->imghght));
		if (!(entities[i++]->img))
			put_err("Failled to generate mlx image from XPM file", solong);
	}
}

int	main(int argc, char *argv[])
{
	t_game	solong;

	solong.mlx_state = 0;
	if (argc < 2)
	   	put_err("Missing map (./maps/<map>.ber)", &solong);
	if (argc > 2)
	    put_err("Too many arguments", &solong);
	if (parse_map(argv[1], &solong))
		put_err("Failled to parse map", &solong);
	put_map(&solong.map, &solong);
	setup_hooks(&solong);
	exit(0);
}
