/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:15:37 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/09 12:03:41 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpt.h"

void		vec_swap(t_vec *pt1, t_vec *pt2)
{
	t_vec	swap;

	if (!pt1 || !pt2)
		return ;
	swap.x = pt1->x;
	swap.y = pt1->y;
	swap.z = pt1->z;
	pt1->x = pt2->x;
	pt1->y = pt2->y;
	pt1->z = pt2->z;
	pt2->x = swap.x;
	pt2->y = swap.y;
	pt2->z = swap.z;
}
