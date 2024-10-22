/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <epinaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:59:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/22 18:48:51 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	*init_map(t_map *map)
{
	map->row_size = 0;
	map->col_size = 0;
	map->size = 0;
	return (map);
}

static int	check_map(t_map *map)
{
	map->exit.x = 0;
	//parsemap
	//check_errors
	//flood_fill
	return (0);
}

static void	assign_elm(char c, size_t xpos, size_t ypos, t_map *map)
{
	map->size++;

	if (c == 'P')
	{
		map->count.player++;
		map->player.x = xpos;
		map->player.y = ypos;
	}
	else if (c == 'C')
		map->count.collectibles++;
	else if (c == 'E')
		map->count.adverse++;
	return ;
}

int	parse_map(char *path)
{
	t_map	map;
	size_t	tmp_rowsiz;
	int		fd;
	char	*row;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (put_err("Error opening file", NULL));
	init_map(&map);
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		map.col_size++;
		tmp_rowsiz = 0;
		while (*row && *row != '\n')
		{
			tmp_rowsiz++;
			if (!ft_strchr("01CEP", *row))
				put_err("Invalid tile / element", NULL);
			else
				assign_elm(*row, tmp_rowsiz, map.col_size, &map);
			row++;
		}
		if (map.row_size > 0 && (tmp_rowsiz != map.row_size))
			put_err("Invalid map dimensions", NULL);
		else if (map.row_size == 0)
			map.row_size = tmp_rowsiz;
		free(row - tmp_rowsiz);
	}
	//check empty map
	close(fd);
	return (check_map(&map));
}