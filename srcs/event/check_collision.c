/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:01:08 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 14:10:13 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

static int			check_map(t_point crd, t_data *data)
{
	t_point		crd_map;

	crd_map = get_map_from_real(&crd);
	if (is_in_map(crd_map.x, crd_map.y, data))
		return (data->map[crd_map.y][crd_map.x]->content);
	return (-1);
}

static t_point		huge_gradient(t_point pt1, t_point pt2, float gradient,
		t_data *data)
{
	t_point		crd;
	int			ret;
	int			incr;

	incr = 1;
	if (pt1.y > pt2.y)
		incr = -1;
	crd = pt_set(pt1.x, pt1.y);
	while (crd.y != pt2.y)
	{
		crd.x = pt1.x + (int)((crd.y - pt1.y) / gradient);
		ret = check_map(crd, data);
		if (ret > 0 || ret == -1)
		{
			crd.x = pt1.x - (int)((crd.y - pt1.y) / gradient);
			crd.y -= incr;
			return (crd);
		}
		crd.y += incr;
	}
	return (crd);
}

static t_point		low_gradient(t_point pt1, t_point pt2, float gradient,
	t_data *data)
{
	t_point		crd;
	int			ret;
	int			incr;

	incr = 1;
	if (pt1.x > pt2.x)
		incr = -1;
	crd = pt_set(pt1.x, pt1.y);
	if (check_map(crd, data) > 0)
		return (crd);
	while (crd.x != pt2.x)
	{
		crd.y = pt1.y + (int)(gradient * (crd.x - pt1.x));
		if ((ret = check_map(crd, data)) > 0)
		{
			crd.y = pt1.y - (int)(gradient * (crd.x - pt1.x));
			crd.x -= incr;
			return (crd);
		}
		crd.x += incr;
	}
	return (crd);
}

t_point				check_collision(t_point old, t_point new, t_data *data)
{
	float		gradient;
	int			divideur;

	divideur = (int)abs(new.x - old.x);
	if (divideur == 0)
		divideur = 1;
	gradient = (float)(old.y - new.y) / divideur;
	if (gradient > -1.5 && gradient < 1.5)
		return (low_gradient(old, new, gradient, data));
	else
		return (huge_gradient(old, new, gradient, data));
}
