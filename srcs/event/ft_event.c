/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetanolliet <gaetanolliet@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:27:24 by fchevrey          #+#    #+#             */
/*   Updated: 2018/12/16 16:04:17 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

static int 	ft_event(SDL_Event *event, t_data *data)
{
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			return (1);
		else if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
			ft_keyboard(event->key.keysym.sym, event->key.repeat, event, data);
		else if (event->type == SDL_MOUSEMOTION)
			ft_mouse(event->motion.x, event->motion.y, data);
		else if (event->type == SDL_MOUSEWHEEL)
			ft_mouse_wheel(event->wheel.y, data);
		else if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE)
		{
			event->type = SDL_KEYDOWN;
			event->key.keysym.sym = SDLK_ESCAPE;
			ft_keyboard(event->key.keysym.sym, event->key.repeat, event, data);
		}
	}
	return (0);
}

void			game_loop(t_data *data)
{
	SDL_Event 			event;
	int					quit;
	const unsigned int	fixdelta = 20;
	unsigned int 		last_time;
	unsigned int 		delta;

	quit = 0;
	data->walking = 0;
	last_time = SDL_GetTicks();
	while (!quit)
	{
		quit = ft_event(&event, data);
		delta += SDL_GetTicks() - last_time;
		if (delta >= fixdelta)
		{
			if (data->walking != MOVE_NONE)
				move(data, ((float)delta /100));
			sound(data); 
			delta = 0.0;
		}
		last_time = SDL_GetTicks();
		loop(data);
	}
	ft_exit(&data);
}
