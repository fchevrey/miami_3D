/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_funar_key_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetanolliet <gaetanolliet@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:42:41 by fchevrey          #+#    #+#             */
/*   Updated: 2018/09/01 19:21:05 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include <stdlib.h>

static t_funar_keyb		add_one(int key, int repeat, void (*f)(t_data*))
{
	t_funar_keyb	item;

	item.key = key;
	item.repeat = repeat;
	item.f = f;
	return (item);
}

t_funar_keyb			*fill_funar_keypress(int *size)
{
	t_funar_keyb	*tab;
	int				nb_fct;
	int				i;

	i = 0;
	*size = 0;
	nb_fct = 11;
	if (!(tab = (t_funar_keyb*)malloc(sizeof(t_funar_keyb) * nb_fct)))
		return (NULL);
	*size = nb_fct;
	/*tab[i++] = add_one(SDLK_UP, &move_foreward);
	tab[i++] = add_one(SDLK_DOWN, &move_backward);
	tab[i++] = add_one(SDLK_LEFT, &look_left_from_key);
	tab[i++] = add_one(SDLK_RIGHT, &look_right_from_key);
	tab[i++] = add_one(SDLK_w, &move_foreward);
	tab[i++] = add_one(SDLK_s, &move_backward);
	tab[i++] = add_one(SDLK_a, &move_left);
	tab[i++] = add_one(SDLK_d, &move_right);*/
	tab[i++] = add_one(SDLK_UP, 0, &move);
	tab[i++] = add_one(SDLK_DOWN, 0, &move);
	tab[i++] = add_one(SDLK_LEFT, 1, &look_left_from_key);
	tab[i++] = add_one(SDLK_RIGHT, 1, &look_right_from_key);
	tab[i++] = add_one(SDLK_w, 0, &move);
	tab[i++] = add_one(SDLK_s, 0, &move);
	tab[i++] = add_one(SDLK_a, 0, &move);
	tab[i++] = add_one(SDLK_d, 0, &move);
	tab[i++] = add_one(SDLK_j, 0, &sound);
	tab[i++] = add_one(SDLK_LCTRL, 0, &crouch);
	tab[i++] = add_one(SDLK_SPACE, 0, &jump);
	return (tab);
}

t_funar_keyb			*fill_funar_keyrelease(int *size)
{
	t_funar_keyb	*tab;
	int				nb_fct;
	int				i;

	i = 0;
	*size = 0;
	nb_fct = 10;
	if (!(tab = (t_funar_keyb*)malloc(sizeof(t_funar_keyb) * nb_fct)))
		return (NULL);
	*size = nb_fct;
	tab[i++] = add_one(SDLK_UP, 0, &check_move);
	tab[i++] = add_one(SDLK_DOWN, 0, &check_move);
	tab[i++] = add_one(SDLK_LEFT, 0, &check_move);
	tab[i++] = add_one(SDLK_RIGHT, 0, &check_move);
	tab[i++] = add_one(SDLK_w, 0, &check_move);
	tab[i++] = add_one(SDLK_s, 0, &check_move);
	tab[i++] = add_one(SDLK_a, 0, &check_move);
	tab[i++] = add_one(SDLK_d, 0, &check_move);
	tab[i++] = add_one(SDLK_LCTRL, 0, &check_stand);
	tab[i++] = add_one(SDLK_SPACE, 0, &check_stand);
	return (tab);
}
