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

float			cast_ray(t_data *data);

/*
** Set offset for applying textures
*/

int				set_offset(t_ptfl hori, t_ptfl verti, float dist_h, float dist_v);


float		return_distance(t_point a, t_ptfl b);

#endif
