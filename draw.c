/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:37:40 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 17:50:07 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Pixel drawing : if = support for little endian, elsif = support for big endian
void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel_pos;
    int		i;

    i = img->bpp - 8;
    pixel_pos = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        if (img->endian != 0)
            *pixel_pos++ = (color >> i) & 0xFF;
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

int	render_loop(t_game *solong)
{
	if (solong->win == NULL)
        return (1);
	//render_background(&solong->img, 0xFFFFFF);
    // render_rect(&solong->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
    //          100, 100, GREEN_PIXEL});
    // render_rect(&solong->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	//mlx_put_image_to_window(solong->mlx, solong->win, solong->img.mlx_img, 0, 0);
    return (0);
}
