/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:08:31 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/22 15:23:56 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmysdl.h"

uint32_t		get_pixel(t_point pt, t_texture *tex)
{
	int				to_color;

	if (!tex)
		return (0);
	if (pt.x >= tex->size.x || pt.y >= tex->size.y || pt.x < 0 || pt.y < 0)
		return (0);
	to_color = (pt.x + (pt.y * tex->size.x));
	return (tex->tab_pxl[to_color]);
}
