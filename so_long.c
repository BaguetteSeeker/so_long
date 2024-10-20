/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/20 22:54:56 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_no_event(void *data)
{
	(void)data;
    return (0);
}

int on_destroy(t_new_game *solong)
{
	mlx_destroy_window(solong->mlx, solong->win);
	mlx_destroy_display(solong->mlx);
	free(solong->mlx);
	exit(0);
	return (0);
}

int	on_keypress(int key_symbol, t_new_game *solong)
{
	if(key_symbol == XK_Escape)
		return (on_destroy(solong));
	// if (varsm)
	// {
	// 	game_map = ft_control_player(keycode, NULL);
	// 	ft_render_basic(game_map, &varsm);
	// }
	return (0);
}

// int	check_map(char *map)
// {
	
// }

//int	player_move

int	main()
{
	t_new_game	solong;

	solong.mlx = mlx_init();
	if (!solong.mlx)
		return (1);
	solong.win = mlx_new_window(solong.mlx, 600, 500, "Oui.");
	if (!solong.win)
		return (free(solong.mlx), 1);
	
	mlx_hook(solong.win, KeyRelease, KeyReleaseMask, &on_keypress, &solong);
	mlx_hook(solong.win, DestroyNotify, StructureNotifyMask, &on_destroy, &solong);
	mlx_loop_hook(solong.win, &handle_no_event, &solong);
		
	ft_printf("Solong started\n");
	mlx_loop(solong.mlx);

}
