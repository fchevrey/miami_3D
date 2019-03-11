/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:01:00 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 14:04:23 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void		check_stand(t_data *data)
{
	const Uint8	*keyboard;

	keyboard = SDL_GetKeyboardState(NULL);
	if (!keyboard[SDL_SCANCODE_LCTRL] && !keyboard[SDL_SCANCODE_SPACE])
		stand(data);
	else if (keyboard[SDL_SCANCODE_LCTRL])
		crouch(data);
	else if (keyboard[SDL_SCANCODE_SPACE])
		jump(data);
}
