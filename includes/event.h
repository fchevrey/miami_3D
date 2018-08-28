/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaetanolliet <gaetanolliet@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:07:31 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/27 11:48:52 by gaetanollie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

#include "main.h"

void			ft_event(t_data *data);
int				ft_mouse(int x, int y, t_data *data);
int				ft_keyboard(int key, int repeat, SDL_Event *event, t_data *data);
int				ft_mouse_wheel(int y, t_data *data);
int				ft_mouse_wheel(int y, t_data *data);
t_funar_keyb	*fill_funar_key_release(int *size);
t_funar_keyb	*fill_funar_key_press(int *size);


/*
** functions that modify data
*/
void			move(t_data *data);
void			move_foreward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			check_move(t_data *data);
void			look_left_from_key(t_data *data);
void			look_right_from_key(t_data *data);
t_point			check_collision(t_point old, t_point new, t_data *data);
void			sound(t_data *data);//

/*
** Jump - stand - crouch
*/
void			check_stand(t_data *data);
void			jump(t_data *data);
void			crouch(t_data *data);
void			stand(t_data *data);

#endif
