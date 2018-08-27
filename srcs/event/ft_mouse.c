/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 20:15:31 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/11 18:56:47 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

int		ft_mouse(int x, int y, t_data *data)
{
	/*data->cam->theta += 1;
	if (data->cam->theta >= 360)
		data->cam->theta -= 360;
	display_map(data->map, data->cam->crd_map->x, data->cam->crd_map->y, data);
	loop(data);
	printf("theta = %f\n", data->cam->theta);*/
	if (x == y && !data)
		return (0);
	return (0);
}
