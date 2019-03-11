/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tex_to_ren.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:18:04 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:24:10 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmysdl.h"

void	put_tex_to_ren(t_texture *tex, SDL_Renderer *ren, t_point crd,
		char put_render)
{
	SDL_Rect		rec;

	rec = (SDL_Rect){crd.x, crd.y, tex->size.x, tex->size.y};
	SDL_UpdateTexture(tex->sdl_tex, NULL, tex->tab_pxl,
			tex->size.x * sizeof(uint32_t));
	SDL_RenderCopy(ren, tex->sdl_tex, NULL, &rec);
	if (put_render == 1)
		SDL_RenderPresent(ren);
}
