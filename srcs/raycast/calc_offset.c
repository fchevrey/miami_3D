#include "raycast.h"
#include <math.h>

int				set_offset(t_ray *act_ray, t_texture *img)
{
	if (act_ray->dist_v < 0 || act_ray->dist_h < act_ray->dist_v)
		act_ray->offset = (int)roundf(act_ray->hori.x) % img->size.x;
	else if (act_ray->dist_h < 0 || act_ray->dist_h > act_ray->dist_v)
		act_ray->offset = (int)roundf(act_ray->verti.y) % img->size.y;
	return (act_ray->offset);
}
