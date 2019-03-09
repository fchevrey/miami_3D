#ifndef RAYCAST_H
#define RAYCAST_H

#include "main.h"

/*
** Draw
*/

//void		ft_ciel_sol(t_data *data);
void            rendering(t_data *dt);

/*
** Detect wall, return distance
*/

float			return_nearest_wall_dist(t_data *data);
t_ptfl			check_walls(t_ptfl point, t_data *data, t_ptfl coeff);
void            horizontal_raycasting(t_data *dt);
void            vertical_raycasting(t_data *dt);

/*
** Set offset for applying textures
*/

//int				set_offset(t_data *data, t_texture *img);
//float		    return_distance(t_point a, t_ptfl b);

#endif
