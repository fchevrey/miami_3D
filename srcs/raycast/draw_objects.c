
#include "main.h"
void			display_objects(t_data *data)
{
	float		obj_dist;
	float		correct_dist;
	float		obj_height;
	t_point		px_to_color;

	obj_dist = cast_ray(data); // envoie un rayon pour connaitre distance
	correct_dist = data->ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta))); // ajuste distance pour fish eyes*/
	obj_height = data->cam->len_cam * (OBJ_H / distance_obj);
	px_to_color = pt_set(data->ray->actual_ray, data->ray->wall_max + 1); // VALEUR PIXEL Y ????????
	while (px_to_color < obj_height)
	{
		pt_to_tex(px_to_color, data->m_img, get_pixel);
		px_to_color.y++;
	}
}

void            display_column(t_data *data)
{
    data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
	ft_ciel_sol(data);
    display_ceiling(data);
    display_wall(data);
}
