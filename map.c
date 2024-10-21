/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:59:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/22 01:05:20 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	*init_map(t_map *map)
{
	map->row_size = 0;
	map->col_size = 0;
	//map->size = 0;
	return (map);
}

static int	check_map(t_map *map)
{
	//parsemap
	//check_errors
	//flood_fill
	return (0);
}

static void	assign_elm(char c, t_map *map)
{
	
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
				assign_elm(*row, &map);
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