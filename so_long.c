/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/21 17:00:10 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel_pos;
    int		i;

    i = img->bpp - 8;
    pixel_pos = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (img->endian != 0)
            *pixel_pos++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel_pos++ = (color >> (img->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

int render_rect(t_img *img, t_rect rect)
{
    int	i;
    int j;

    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            img_pix_put(img, j++, i, rect.color);
        ++i;
    }
    return (0);
}

void	render_background(t_img *img, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            img_pix_put(img, j++, i, color);
        ++i;
    }
}

int	render_game(t_data *solong)
{
	if (solong->win == NULL)
        return (1);

	render_background(&solong->img, 0xFFFFFF);
    render_rect(&solong->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
            100, 100, GREEN_PIXEL});
    render_rect(&solong->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	mlx_put_image_to_window(solong->mlx, solong->win, solong->img.mlx_img, 0, 0);
    return (0);
}

int on_destroy(t_data *solong)
{
	mlx_destroy_window(solong->mlx, solong->win);
	mlx_destroy_display(solong->mlx);
	free(solong->mlx);
	exit(0);
	return (0);
}

int	on_keypress(int key_symbol, t_data *solong)
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
	t_data	solong;

	// if (argc == 1)
	// 	ft_printf(&solong, "Missing map (./so_long maps/intra.ber)");
	// if (argc > 2)
	// 	ft_printf(&solong, "Too many arguments");
	solong.mlx = mlx_init();
	if (!solong.mlx)
		return (1);
	solong.win = mlx_new_window(solong.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Oui.");
	if (!solong.win)
		return (free(solong.mlx), 1);

	solong.img.mlx_img = mlx_new_image(solong.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	solong.img.addr = mlx_get_data_addr(solong.img.mlx_img, &solong.img.bpp, &solong.img.line_len, &solong.img.endian);
			
	ft_printf("Solong started\n");
	mlx_loop_hook(solong.mlx, &render_game, &solong);
	mlx_hook(solong.win, KeyRelease, KeyReleaseMask, &on_keypress, &solong);
	mlx_hook(solong.win, DestroyNotify, StructureNotifyMask, &on_destroy, &solong);

	mlx_loop(solong.mlx);
	on_destroy(&solong);
}
