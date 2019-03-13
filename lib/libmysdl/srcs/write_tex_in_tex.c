/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tex_in_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:13:30 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:42:19 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmysdl.h"

void	write_tex_in_tex(t_texture *to_write_in, t_texture *tex,
		t_point begin)
{
	t_point			crd_child;
	t_point			crd;
	int				i;
	int				j;

	if (!tex)
		return ;
	crd_child = pt_set(0, 0);
	crd = pt_set(begin.x, begin.y);
	i = 0;
	while (crd_child.x < tex->size.x)
	{
		j = 0;
		crd_child.y = 0;
		crd.y = begin.y;
		while (crd_child.y < tex->size.y && ++j)
		{
			pt_to_tex(crd, to_write_in, get_pixel(crd_child, tex));
			crd_child.y++;
			crd.y++;
		}
		crd_child.x++;
		crd.x++;
	}
}
