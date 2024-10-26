/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/26 02:44:26 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//int	player_move
int	put_err(char *msg, t_game *solong, int mlx_initialized)
{
	perror(msg);
	if (mlx_initialized)
		on_destroy(solong);
	exit(EXIT_FAILLURE);
}

//void  flood_fill(char **tab, t_point size, t_point begin);

//void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);

int	main(int argc, char *argv[])
{
	t_game	solong;

	if (argc < 2)
	   	put_err("Missing map (./so_long/maps/<map>.ber)", &solong, MLX_OFF);
	if (argc > 2)
	    put_err("Too many arguments", &solong, MLX_OFF);
	if (parse_map(argv[1], &solong))
		return (1);
	solong.mlx = mlx_init();
	if (!solong.mlx)
		return (1);
	//parse map
	//draw map
	//enable actions
	//mlx_xpm_file_to_image(void *mlx, char *filename, int *width, int *height);
	solong.win = mlx_new_window(solong.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Oui.");
	if (!solong.win)
		return (free(solong.mlx), 1);

	solong.img.mlx_img = mlx_new_image(solong.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	solong.img.addr = mlx_get_data_addr(solong.img.mlx_img, &solong.img.bpp, &solong.img.line_len, &solong.img.endian);
	setup_hooks(&solong);
	on_destroy(&solong);
}
