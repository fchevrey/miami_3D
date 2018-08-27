/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:08:14 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/22 15:22:59 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmysdl.h"
#include <stdlib.h>

void		free_tex(t_texture **tex)
{
	if (!tex || !*tex)
		return ;
	free((*tex)->tab_pxl);
	(*tex)->tab_pxl = NULL;
	SDL_DestroyTexture((SDL_Texture*)(*tex)->sdl_tex);
	free(*tex);
	*tex = NULL;
}
