
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
	int		ray;
	float	angle;
	float	distance_wall;
	float	size_wall;
	int		offset;
	t_point	crd;

	ft_ciel_sol(data);
	angle = data->cam->theta + FOV / 2;
	crd = pt_set(0,500);
	if (angle > 360)
		angle = angle - 360;
	ray = 0;
	while (ray < WIN_WIDTH)
	{
		distance_wall = cast_ray(angle, data, &offset); // envoie un rayon pour connaitre distance
		distance_wall = distance_wall * cos(fabs(deg_to_rad(angle - data->cam->theta))); // ajuste distance pour fish eyes*/
		size_wall = data->cam->len_cam * (WALL_H / distance_wall);
		display_line_wall(data, size_wall, ray, offset);
		if (angle - data->cam->min_theta < 0)
			angle = 360 + (angle - data->cam->min_theta);
		else
			angle -= data->cam->min_theta;
		ray++;
	}
//	mini_map(data);
	put_tex_to_ren(data->m_img, data->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(data->b_and_w_tiles, data->win->ren, crd, 1);
}
