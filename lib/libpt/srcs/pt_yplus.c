/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_yplus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:59:18 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/09 12:05:35 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpt.h"

void			pt_yplus(t_point *src, int ymin, int ymax)
{
	src->y++;
	if (src->y > ymax)
	{
		src->y = ymin;
		src->x++;
	}
}
