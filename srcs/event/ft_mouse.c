/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 20:15:31 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 11:03:52 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "raycast.h"

static void		look_left(t_data *data, int delta)
{
	data->cam->theta += ((float)delta) / 3;
	while (data->cam->theta >= 360)
		data->cam->theta -= 360;
//	rendering(data);
}

static void		look_right(t_data *data, int delta)
{
	data->cam->theta -= ((float)delta) / 3;
	while (data->cam->theta < 0)
		data->cam->theta += 360;
//	rendering(data);
}

int		ft_mouse(int x, int y, t_data *data)
{
	static int		_x = 0;

	if (!data)
		return (0);
	if (x < _x)
	{
		look_left(data, _x - x);
	}
	else if (x > _x)
	{
		look_right(data, x - _x);
	}
	y = x;
	_x = x;
	return (0);
}
