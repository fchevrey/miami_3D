/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:07:31 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/21 15:59:01 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

#include "main.h"

void			ft_event(t_data *data);
int				ft_mouse(int x, int y, t_data *data);
int				ft_keyboard(int key, uint8_t repeat, t_data *data);
int				ft_mouse_wheel(int y, t_data *data);
int				ft_mouse_wheel(int y, t_data *data);
t_funar_keyb	*fill_funar_key_event(int *size);

/*
** functions that modify data
*/
void			move(t_data *data, int movement);
void			move_foreward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			look_left_from_key(t_data *data);
void			look_right_from_key(t_data *data);
t_point			check_collision(t_point old, t_point new, t_data *data);
void			sound(t_data *data);//

#endif
