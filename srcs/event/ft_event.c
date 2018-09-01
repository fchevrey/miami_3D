/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetanolliet <gaetanolliet@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:27:24 by fchevrey          #+#    #+#             */
/*   Updated: 2018/09/01 21:03:06 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

/*static void		key_up(SDL_Event *event, t_data *data)
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
}*/

void	ft_event(t_data *data)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	data->walking = 0;
	while (!quit)
	{
		if (SDL_WaitEventTimeout(&event, 50))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
			else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
				ft_keyboard(event.key.keysym.sym, event.key.repeat, &event, data);
			else if (event.type == SDL_MOUSEMOTION)
				ft_mouse(event.motion.x, event.motion.y, data);
			else if (event.type == SDL_MOUSEWHEEL)
				ft_mouse_wheel(event.wheel.y, data);
			else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				event.type = SDL_KEYDOWN;
				event.key.keysym.sym = SDLK_ESCAPE;
				ft_keyboard(event.key.keysym.sym, event.key.repeat, &event, data);
			}
		}
		if (data->walking != MOVE_NONE)
			move(data);
	}
	ft_exit(&data);
}
