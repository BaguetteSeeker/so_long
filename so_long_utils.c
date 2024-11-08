/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 01:38:00 by epinaud           #+#    #+#             */
/*   Updated: 2024/11/08 17:50:02 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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