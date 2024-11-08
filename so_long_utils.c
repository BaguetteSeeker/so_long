/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 01:38:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 23:33:00 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_entity	*fetch_entity(char c, t_game *solong)
{
	int	pos;

	pos = 0;
	while (ALLOWED_ELEMS[pos] && ALLOWED_ELEMS[pos] != c)
		pos++;
	if (!ALLOWED_ELEMS[pos])
		return (NULL);
	return (solong->map.entities[pos]);
}

int	in_array(int val, int tab[], size_t siz)
{
	size_t	pos;

	pos = 0;
	while (pos != siz)
	{
		if (tab[pos] == val)
			return (pos);
		pos++;
	}
	return (-1);
}
