/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/11 04:10:12 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	solong;

	solong.mlx_state = 0;
	if (argc < 2)
		put_err("Missing map (./maps/<map>.ber)", &solong);
	if (argc > 2)
		put_err("Too many arguments", &solong);
	if (parse_map(argv[1], &solong))
		put_err("Failled to parse map", &solong);
	put_map(&solong.map, &solong);
	setup_hooks(&solong);
	exit(0);
}
