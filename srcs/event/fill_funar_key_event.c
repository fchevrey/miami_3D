/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_funar_key_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetanolliet <gaetanolliet@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:42:41 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/27 11:50:13 by gaetanollie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include <stdlib.h>

static t_funar_keyb		add_one(int key, void (*f)(t_data*))
{
	t_funar_keyb	item;

	item.key = key;
	item.f = f;
	return (item);
}

t_funar_keyb			*fill_funar_key_press(int *size)
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
	tab[i++] = add_one(SDLK_UP, &move);
	tab[i++] = add_one(SDLK_DOWN, &move);
	tab[i++] = add_one(SDLK_LEFT, &look_left_from_key);
	tab[i++] = add_one(SDLK_RIGHT, &look_right_from_key);
	tab[i++] = add_one(SDLK_w, &move);
	tab[i++] = add_one(SDLK_s, &move);
	tab[i++] = add_one(SDLK_a, &move);
	tab[i++] = add_one(SDLK_d, &move);
	tab[i++] = add_one(SDLK_j, &sound);
	tab[i++] = add_one(SDLK_LCTRL, &crouch);
	tab[i++] = add_one(SDLK_SPACE, &jump);
	return (tab);
}

t_funar_keyb			*fill_funar_key_release(int *size)
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
	tab[i++] = add_one(SDLK_UP, &check_move);
	tab[i++] = add_one(SDLK_DOWN, &check_move);
	tab[i++] = add_one(SDLK_LEFT, &check_move);
	tab[i++] = add_one(SDLK_RIGHT, &check_move);
	tab[i++] = add_one(SDLK_w, &check_move);
	tab[i++] = add_one(SDLK_s, &check_move);
	tab[i++] = add_one(SDLK_a, &check_move);
	tab[i++] = add_one(SDLK_d, &check_move);
	tab[i++] = add_one(SDLK_LCTRL, &check_stand);
	tab[i++] = add_one(SDLK_SPACE, &check_stand);
	return (tab);
}