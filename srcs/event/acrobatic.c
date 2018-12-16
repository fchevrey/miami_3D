/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acrobatic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:00:59 by fchevrey          #+#    #+#             */
/*   Updated: 2018/12/16 16:01:42 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	stand(t_data *data)
{
	data->cam->h_cam = 0.5;
	data->cam->len_cam = (WIN_WIDTH * data->cam->h_cam) / tan(deg_to_rad(FOV * data->cam->h_cam));
	loop(data);
}

void	crouch(t_data *data)
{
	data->cam->h_cam = 0.9;
	data->cam->len_cam = (WIN_WIDTH * data->cam->h_cam) / tan(deg_to_rad(FOV * data->cam->h_cam));
	loop(data);
}

void	jump(t_data *data)
{
	data->cam->h_cam = 0.3;
	data->cam->len_cam = (WIN_WIDTH * data->cam->h_cam) / tan(deg_to_rad(FOV * data->cam->h_cam));
	loop(data);
}
