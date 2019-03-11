/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nearest_wall_distance.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenetea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:41:01 by cbenetea          #+#    #+#             */
/*   Updated: 2019/03/11 19:41:19 by cbenetea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raycast.h"

int					is_in_map(float x, float y, t_data *data)
{
	if (x < 0.0 || x > (float)data->xmax)
		return (0);
	if (y < 0.0 || y > (float)data->ymax)
		return (0);
	return (1);
}

t_ptfl				return_pos_map(float x, float y)
{
	t_ptfl			map;

	map.x = (x / (float)SIZE_GRID);
	map.y = (y / (float)SIZE_GRID);
	return (map);
}

t_ptfl				check_walls(t_ptfl point, t_data *data, t_ptfl coeff)
{
	t_ptfl			pt_map;

	pt_map = return_pos_map(point.x, point.y);
	if (is_in_map(pt_map.x, pt_map.y, data) == 0)
		return (point);
	while (data->map[(int)(pt_map.y)][(int)(pt_map.x)]->content != 1)
	{
		point.x += coeff.x;
		point.y += coeff.y;
		pt_map = return_pos_map(point.x, point.y);
		if (is_in_map(pt_map.x, pt_map.y, data) == 0)
			return (point);
	}
	return (point);
}

float				return_nearest_wall_dist(t_data *dt)
{
	dt->ray->hori = (t_ptfl){0, 0};
	dt->ray->verti = dt->ray->hori;
	dt->ray->dist_h = -1;
	dt->ray->dist_v = -1;
	horizontal_raycasting(dt);
	vertical_raycasting(dt);
	if (dt->ray->dist_h < 0 || dt->ray->dist_v < dt->ray->dist_h)
		return (dt->ray->dist_v);
	else if (dt->ray->dist_v < 0 || dt->ray->dist_h < dt->ray->dist_v)
		return (dt->ray->dist_h);
	return (dt->ray->dist_h);
}
