/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:49:51 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/14 11:05:25 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "main.h"

void			game_loop(t_data *data);
int				ft_mouse(int x, int y, t_data *data);
int				ft_keyboard(int key, int repeat, SDL_Event *event,
		t_data *data);
int				ft_mouse_wheel(int y, t_data *data);
int				ft_mouse_wheel(int y, t_data *data);
t_funar_keyb	*fill_funar_keyrelease(int *size);
t_funar_keyb	*fill_funar_keypress(int *size);
void			play_walk_sound(t_data *data);
void			play_shot_sound(t_data *data);

/*
** functions that modify data
*/

void			move(t_data *data, float deltatime);
void			move_foreward(t_data *data, float deltatime, const int speed);
void			move_backward(t_data *data, float deltatime, const int speed);
void			move_left(t_data *data, float deltatime, const int speed);
void			move_right(t_data *data, float deltatime, const int speed);
void			check_move(t_data *data);
void			look_left_from_key(t_data *data);
void			look_right_from_key(t_data *data);
void			sound(t_data *data);
void			next_song(t_data *data);

#endif
