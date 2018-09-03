
#include "main.h"

int         is_in_map(int x, int y, t_data *data)
{
	if (x > data->xmax || x < 0)
		return (0);
	if (y > data->ymax || y < 0)
		return (0);
	return (1);
}

float       return_fish(float deg, float vision)
{
	return (fabsf(deg - vision));
}

void        loop(t_data *data)
{
	float	distance_wall;

	data->ray->deg = data->cam->theta + FOV / 2;
	if (data->ray->deg > 360)
		data->ray->deg = data->ray->deg - 360;
	printf("VALEUR PREMIER ANGLE = %f\n", data->ray->deg);
	data->ray->actual_ray = 0;
	while (data->ray->actual_ray < WIN_WIDTH)
	{
		data->ray->dist_w_d = cast_ray(data); // envoie un rayon pour connaitre distance
		distance_wall = data->ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta))); // ajuste distance pour fish eyes*/
		data->ray->wall_size = data->cam->len_cam * (WALL_H / distance_wall);
		display_column(data);
		if (data->ray->deg - data->cam->min_theta < 0)
			data->ray->deg = 360 + (data->ray->deg - data->cam->min_theta);
		else
			data->ray->deg -= data->cam->min_theta;
		data->ray->actual_ray++;
	}
	draw_mini_map2(data);
	put_tex_to_ren(data->m_img, data->win->ren, (t_point){0, 0}, 0);
//	put_tex_to_ren(data->b_and_w_tiles, data->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(data->hud, data->win->ren, pt_set(0, data->m_img->size.y), 1);
}
