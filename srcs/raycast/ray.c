
#include "main.h"

int         is_in_map(float x, float y, t_data *data)
{
	if (x < 0.0 || x > (float)data->xmax)
		return (0);
	if (y < 0.0 || y > (float)data->ymax)
		return (0);
	return (1);
}

float       return_fish(float deg, float vision)
{
	return (fabsf(deg - vision));
}

void        loop(t_data *dt)
{
	float	distance_wall;
/*	float	test;

	test = 0.0;
	while (test < 360)
	{
		printf("tan de %f = %f \n", test, tan(deg_to_rad(test)));
		test += 0.1;
	}*/
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
		dt->ray->actual_ray++;
	}
	draw_mini_map2(dt);
	put_tex_to_ren(dt->m_img, dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->wall_texts[0], dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->hud, dt->win->ren, pt_set(0, dt->m_img->size.y), 1);
}
