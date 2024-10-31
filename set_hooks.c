/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:45:08 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/31 18:18:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int destroy_mlx(t_game *solong)
{
    ft_putendl_fd("Entered destruction state;\n", 1);
	//ft_clean_memtree(solong->map->grid);
	mlx_clear_window(solong->mlx, solong->win);
	mlx_destroy_window(solong->mlx, solong->win);
	mlx_destroy_image(solong->mlx, solong->img.mlx_img);
	mlx_destroy_display(solong->mlx);
	printf("Grid ptr is: %p\n", solong->map.grid);
	solong->map.grid = ft_clean_memtree(solong->map.grid);
	free(solong->mlx);
	//exit(1);
	return (1);
}

int	on_keypress(int key_symbol, t_game *solong)
{
	if(key_symbol == XK_Escape)
		exit(destroy_mlx(solong));
	return (0);
}

void    setup_hooks(t_game *solong)
{
	ft_putendl_fd("Setting up hooks\n", 1);
	mlx_loop_hook(solong->mlx, &render_loop, solong);
	mlx_hook(solong->win, KeyRelease, KeyReleaseMask, &on_keypress, solong);
	mlx_hook(solong->win, DestroyNotify, StructureNotifyMask, &destroy_mlx, solong);
	mlx_loop(solong->mlx);
}