/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:27:24 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/22 19:44:33 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

static void		key_up(SDL_Event *event, t_data *data)
{
	int		key;

	key = event->key.keysym.sym;
	if (!data)
		return ;
	if (key == SDLK_UP || key == SDLK_DOWN)
	{
		data->walking = MOVE_NONE;
		Mix_Pause(data->walk_channel);
	}
}

void	ft_event(t_data *data)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	data->walking = 0;
	printf("real x = %d y = %d, mapx = %d y = %d\n", data->cam->crd_real->x, data->cam->crd_real->y, data->cam->crd_map->x, data->cam->crd_map->y);
	while (!quit)
	{
		if (SDL_WaitEventTimeout(&event, 20))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
				ft_keyboard(event.key.keysym.sym, event.key.repeat, data);
			else if (event.type == SDL_KEYUP)
				key_up(&event, data);
			else if (event.type == SDL_MOUSEMOTION)
				ft_mouse(event.motion.x, event.motion.y, data);
			else if (event.type == SDL_MOUSEWHEEL)
				ft_mouse_wheel(event.wheel.y, data);
		}
		if (data->walking != MOVE_NONE)
			move(data, data->walking);
	}
	ft_exit(&data);
}
