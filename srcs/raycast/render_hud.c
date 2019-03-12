/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:42:44 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/12 19:27:50 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raycast.h"

void			render_hud(t_data *dt)
{
	t_point			begin;
	t_texture		*tex;

	put_tex_to_ren(dt->hud, dt->win->ren, pt_set(0, dt->m_img->size.y), 0);
	put_tex_to_ren(dt->texts[1], dt->win->ren, pt_set(30, dt->m_img->size.y + 10), 0);
	put_tex_to_ren(dt->texts[2], dt->win->ren, pt_set(200, dt->m_img->size.y + 10), 0);
	tex = dt->texts[0];
	begin.y = dt->m_img->size.y - tex->size.y;
	begin.x = (dt->m_img->size.x - tex->size.x) / 2;
	put_tex_to_ren(dt->texts[0], dt->win->ren, begin, 1);
}
