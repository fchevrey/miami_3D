
#include "main.h"

int         is_in_map(float x, float y, t_data *data)
{
	if (x > (float)data->xmax || x < 0)
		return (0);
	if (y > (float)data->ymax || y < 0)
		return (0);
	return (1);
}

float       return_fish(float deg, float vision)
{
	return (fabsf(deg - vision));
}

void        display_obj(t_data *dt)
{
	float	distance_wall;
	int		i;
	int		tmp;

	while (data->obj_test[i].content != -1.0)
	{
		dt->ray->deg = dt->cam->theta + FOV / 2;
	if (dt->ray->deg > 360)
		dt->ray->deg = dt->ray->deg - 360;
	dt->ray->actual_ray = 0;
	while (dt->ray->actual_ray < WIN_WIDTH)
	{

		dt->ray->dist_w_d = cast_ray(dt);
		distance_wall = dt->ray->dist_w_d * cos(fabs(deg_to_rad(dt->ray->deg
		- dt->cam->theta)));
		dt->ray->wall_size = dt->cam->len_cam * (WALL_H / distance_wall);
		display_column(dt);
		if (dt->ray->deg - dt->cam->min_theta < 0)
			dt->ray->deg = 360 + (dt->ray->deg - dt->cam->min_theta);
		else
			dt->ray->deg -= dt->cam->min_theta;
		if (tmp != dt->obj_ar[i].content)
		{
			dt->obj_ar[i].wall_dist = wall_dist;
			i++;
		}
		dt->ray->actual_ray++;
	}
}
