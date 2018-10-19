#ifndef RAYCAST_H
#define RAYCAST_H

#include "main.h"

/*
** Draw
*/

//void		ft_ciel_sol(t_data *data);
void            display_column(t_data *dt, t_ray *act_ray);
void            display_objects(t_data *data);

/*
** Detect wall, return distance
*/

void			cast_ray(t_data *data, t_ray *act_ray);

/*
** Set offset for applying textures
*/

int				set_offset(t_ray *act_ray, t_texture *img);


float		return_distance(t_point a, t_ptfl b);

#endif
