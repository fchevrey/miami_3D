/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 20:15:31 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:47:55 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "raycast.h"

static void		look_left(t_data *data, int delta)
{
	data->cam->theta += ((float)delta) / 3;
	while (data->cam->theta >= 360)
		data->cam->theta -= 360;
}

static void		look_right(t_data *data, int delta)
{
	data->cam->theta -= ((float)delta) / 3;
	while (data->cam->theta < 0)
		data->cam->theta += 360;
}

int				ft_mouse(int x, int y, t_data *data)
{
	static int		static_x = 0;

	if (!data)
		return (0);
	if (x < static_x)
	{
		look_left(data, static_x - x);
	}
	else if (x > static_x)
	{
		look_right(data, x - static_x);
	}
	y = x;
	static_x = x;
	return (0);
}
