#ifndef RAYCAST_H
#define RAYCAST_H

#include "main.h"


/*
** Draw
*/

void		ft_ciel_sol(t_data *data);
void		display_line_wall(t_data *data, float wall_size, int x, int offset);

/*
** Detect wall, return distance
*/

float       cast_ray(float deg, t_data *data, int *offset);


/*
** Set offset for applying textures
*/

int		set_offset(t_point hori, t_point verti, float dist_h, float dist_v);

#endif
