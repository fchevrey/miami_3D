/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:58:56 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 18:04:18 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_point		find_start(t_map ***map)
{
	int		x;
	int		y;

	y = 1;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x])->content == 0)
				return (pt_set(x, y));
			x++;
		}
		y++;
	}
	return (pt_set(-1, -1));
}
