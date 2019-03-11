/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_funar_key_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:09:38 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 14:09:40 by fchevrey         ###   ########.fr       */
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
	nb_fct = 12;
	if (!(tab = (t_funar_keyb*)malloc(sizeof(t_funar_keyb) * nb_fct)))
		return (NULL);
	*size = nb_fct;
	tab[i++] = add_one(SDLK_UP, 0, &check_move);
	tab[i++] = add_one(SDLK_DOWN, 0, &check_move);
	tab[i++] = add_one(SDLK_LEFT, 1, &look_left_from_key);
	tab[i++] = add_one(SDLK_RIGHT, 1, &look_right_from_key);
	tab[i++] = add_one(SDLK_w, 0, &check_move);
	tab[i++] = add_one(SDLK_s, 0, &check_move);
	tab[i++] = add_one(SDLK_a, 0, &check_move);
	tab[i++] = add_one(SDLK_d, 0, &check_move);
	tab[i++] = add_one(SDLK_j, 0, &sound);
	tab[i++] = add_one(SDLK_k, 0, &next_song);
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
