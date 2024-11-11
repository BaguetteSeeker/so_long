/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:45:08 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/11 07:34:49 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_err(char *msg, t_game *solong)
{
	ft_putendl_fd("Error", 1);
	if (errno)
		perror(msg);
	else
		ft_putendl_fd(msg, 1);
	clean_game_memory(solong);
	exit(EXIT_FAILLURE);
}

int	on_keypress(int keysym, t_game *solong)
{
	if (keysym == XK_Escape)
		exit(close_game("", solong));
	else if (in_array(keysym, MOV_KEYS, sizeof(MOV_KEYS) / 4) != -1)
		move_player(keysym, &(solong->map.pchr_pos), solong);
	return (0);
}

int	close_game(char *closure_msg, t_game *solong)
{
	ft_putendl_fd(closure_msg, 1);
	clean_game_memory(solong);
	ft_putendl_fd("Closing game..\n\n..\n", 1);
	exit(0);
}

//Roots DestroyNotify event to close_game with its TWO required params
int	cross_close(t_game *solong)
{
	close_game("", solong);
	return (0);
}

//mlx_loop_hook(solong->mlx, &render_loop, solong);
void	setup_hooks(t_game *solong)
{
	ft_putendl_fd("Setting up hooks\n", 1);
	mlx_hook(solong->win, KeyRelease, KeyReleaseMask, &on_keypress, solong);
	mlx_hook(solong->win, DestroyNotify, StructureNotifyMask,
		&cross_close, solong);
	mlx_loop(solong->mlx);
}
