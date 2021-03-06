/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:46:48 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:46:50 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_black_square(t_data *data)
{
	t_point	crd;

	crd.y = -1;
	while (++crd.y < HUD_HEIGHT)
	{
		crd.x = data->hud->size.x - HUD_HEIGHT;
		while (++crd.x < data->hud->size.x)
			pt_to_tex(crd, data->hud, SQUARE_COLOR);
	}
}

void	draw_square(t_data *data, t_point crd, int size, int color)
{
	t_point	pt;
	t_point tmp;
	t_point added;

	pt.x = HUD_HEIGHT / 2 - ((size * data->xmax + 1) / 2 + size / 2) \
		+ (data->hud->size.x - HUD_HEIGHT + crd.x * size);
	pt.y = (HUD_HEIGHT / 2 - ((size * data->ymax + 1) / 2 \
		+ (((data->ymax + 1) % 2) * size / 2)) + (crd.y * size));
	tmp.y = -1;
	while (++tmp.y < size)
	{
		tmp.x = -1;
		while (++tmp.x < size)
		{
			added.x = pt.x + tmp.x;
			added.y = pt.y + tmp.y;
			pt_to_tex(added, data->hud, color);
		}
	}
}

void	draw_mini_map(t_data *data)
{
	t_point crd;
	int		size;

	size = 12;
	while (--size > 2)
		if (((data->xmax + 1) * size) < HUD_HEIGHT - (size * 2) \
			&& ((data->ymax + 1) * size) < HUD_HEIGHT - (size * 2))
			break ;
	draw_black_square(data);
	crd.y = -1;
	while (++crd.y <= data->ymax)
	{
		crd.x = -1;
		while (++crd.x <= data->xmax)
		{
			if (crd.x == data->cam->crd_map->x \
					&& crd.y == data->cam->crd_map->y)
				draw_square(data, crd, size, 0xFFFF88A6);
			else if (data->map[crd.y][crd.x]->content == 1)
				draw_square(data, crd, size, 0xFFA6A6A6);
			else
				draw_square(data, crd, size, 0xFFFFFFFF);
		}
	}
}
