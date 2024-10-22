/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <epinaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:45:08 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/22 19:52:02 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int on_destroy(t_game *solong)
{
    ft_putendl_fd("Entered destruction state;", 1);
	mlx_destroy_window(solong->mlx, solong->win);
	mlx_destroy_display(solong->mlx);
	free(solong->mlx);
	exit(0);
}

int	on_keypress(int key_symbol, t_game *solong)
{
	if(key_symbol == XK_Escape)
		return (on_destroy(solong));
	return (0);
}

void    setup_hooks(t_game *solong)
{
	ft_putendl_fd("Setting up hooks\n", 1);
	mlx_loop_hook(solong->mlx, &render_loop, solong);
	mlx_hook(solong->win, KeyRelease, KeyReleaseMask, &on_keypress, solong);
	mlx_hook(solong->win, DestroyNotify, StructureNotifyMask, &on_destroy, solong);
	mlx_loop(solong->mlx);
}