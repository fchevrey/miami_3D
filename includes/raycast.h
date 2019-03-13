/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:40:15 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:40:17 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "main.h"

/*
** Draw
*/

void			rendering(t_data *dt);

/*
** Detect wall, return distance
*/

float			return_nearest_wall_dist(t_data *data);
t_ptfl			check_walls(t_ptfl point, t_data *data, t_ptfl coeff);
void			horizontal_raycasting(t_data *dt);
void			vertical_raycasting(t_data *dt);
t_ptfl			vertical_up(t_data *data, float deg);
t_ptfl			vertical_down(t_data *data, float deg);
t_ptfl			horizon_right(t_data *data, float deg);
t_ptfl			horizon_left(t_data *data, float deg);
float			return_distance(t_point a, t_ptfl b);
void			render_hud(t_data *dt);

#endif
