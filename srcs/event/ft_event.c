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
#include <time.h>

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
	SDL_Event		event;
	int				quit;
	double 			delta;
	const double	fixdelta = 0.02;	
	time_t			last_time;

	quit = 0;
	data->walking = 0;
	time(&last_time);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
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
		//tim _ deltaTime
		delta += difftime(last_time, time(NULL));
		//physics checks
		printf("dela = %f\n", delta);
		if (delta >= fixdelta)
		{
			if (data->walking != MOVE_NONE)
				move(data, (float)delta);
			sound(data); 
			delta = 0.0;
		}
		time(&last_time);
		//render
	}
	ft_exit(&data);
}
