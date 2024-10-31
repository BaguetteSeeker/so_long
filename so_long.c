/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/31 12:57:30 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//int	player_move
int	put_err(char *msg, t_game *solong, int mlx_instance)
{
	perror(msg);
	if (mlx_instance == MLX_ON)
		destroy_mlx(solong);
	ft_clean_memtree(solong->map.grid);
	exit(EXIT_FAILLURE);
}

//void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
//void  flood_fill(char **tab, t_point size, t_point begin);

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
	printf("Main map grid is: %p\n", solong.map.grid);
	solong.mlx = mlx_init();
	printf("Main map grid2 is: %p && mlx ptr is %p\n", solong.map.grid, solong.mlx);
	//printf("Weird data is %s\n", *(solong.map->grid));
	if (!solong.mlx)
		put_err("Failed to initialize MLX", &solong, MLX_OFF);
	// while (*solong.map->grid)
	// {
	// 	ft_putendl_fd(*(solong.map->grid)++, 1);
	// }
	
	//parse map
	//draw map
	//enable actions
	//mlx_xpm_file_to_image(void *mlx, char *filename, int *width, int *height);
	//check xpm alloc
	solong.win = mlx_new_window(solong.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
	if (!solong.win)
		return (free(solong.mlx), 1);
	solong.img.mlx_img = mlx_new_image(solong.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	solong.img.addr = mlx_get_data_addr(solong.img.mlx_img, &solong.img.bpp, &solong.img.line_len, &solong.img.endian);
	setup_hooks(&solong);
	//destroy_mlx(&solong);
	exit(0);
}
