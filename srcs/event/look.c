/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:00:07 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 14:00:08 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	look_left_from_key(t_data *data)
{
	data->cam->theta += 10;
	if (data->cam->theta >= 360)
		data->cam->theta -= 360;
	rendering(data);
}

void	look_right_from_key(t_data *data)
{
	data->cam->theta -= 10;
	if (data->cam->theta < 0)
		data->cam->theta += 360;
	rendering(data);
}
