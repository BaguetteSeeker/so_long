/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:06:02 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/11 07:11:04 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	solong;

	solong = (t_game){};
	solong.mlx_state = 0;
	if (argc < 2)
		put_err("Missing map (./maps/<map>.ber)", &solong);
	else if (argc > 2)
		put_err("Too many arguments", &solong);
	if (!ft_strnstr(&(argv[1][ft_strlen(argv[1])]) - 4, ".ber", 4))
		put_err("Wrong or missing file extension (.ber)", &solong);
	if (parse_map(argv[1], &solong))
		put_err("Failled to parse map", &solong);
	put_map(&solong.map, &solong);
	setup_hooks(&solong);
	exit(0);
}
