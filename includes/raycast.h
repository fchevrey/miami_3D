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
void			horizontal_raycasting(t_data *dt);
void			vertical_raycasting(t_data *dt);
t_ptfl			vertical_up(t_data *data, float deg);
t_ptfl			vertical_down(t_data *data, float deg);
t_ptfl			horizon_right(t_data *data, float deg);
t_ptfl			horizon_left(t_data *data, float deg);
float			return_distance(t_point a, t_ptfl b);

/*
** Set offset for applying textures
*/

//int				set_offset(t_data *data, t_texture *img);
//float		    return_distance(t_point a, t_ptfl b);

#endif
