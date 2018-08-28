#ifndef RAYCAST_H
#define RAYCAST_H

#include "main.h"

/*
** Draw
*/

//void		ft_ciel_sol(t_data *data);
void            display_column(t_data *data);

/*
** Detect wall, return distance
*/

float				cast_ray(t_data *data);
t_ptfl				vertical_down(t_data *data, float deg);
t_ptfl				vertical_up(t_data *data, float deg);
t_ptfl				horizon_right(t_data *data, float deg);
t_ptfl				horizon_left(t_data *data, float deg);
float			return_distance(t_point a, t_ptfl b);

/*
** Set offset for applying textures
*/

int				set_offset(t_ptfl hori, t_ptfl verti, float dist_h, float dist_v);


#endif
