
#include "main.h"

static void		sort_obj_by_distance(t_data *dt)
{
	int			i;
	t_obj		tmp;

	i = 0;
	while (dt->obj_ar[i].content != -1)
	{
		if (dt->obj_ar[i + 1].obj_dist > dt->obj_ar[i].obj_dist)
		{
			tmp = dt->obj_ar[i];
			dt->obj_ar[i] = dt->obj_ar[i + 1];
			dt->obj_ar[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

static void		calc_obj_distance(t_data *dt)
{
	int			i;

	i = 0;
	while (dt->obj_ar[i].content != -1)
	{
		dt->obj_ar[i].obj_dist = sqrt(pow((dt->obj_ar[i].obj_pt.x - dt->cam->crd_real.x),2) + pow((dt->obj_ar[i].obj_pt.y - dt->cam->crd_real.y), 2));
		i++;
	}
}

static void		calc_obj_height(t_data *dt)
{
	int			i;

	i = 0;
	while (dt->obj_ar[i].content != -1)
	{
		dt->obj_ar[i].obj_height = data->cam->len_cam * (OBJ_H / dt->obj_ar[i].obj_dist);
		i++;
	}
}

void			display_objects(t_data *dt)
{
	float		obj_dist;
	float		correct_dist;
	float		obj_height;
	t_point		px_to_color;

	calc_obj_distance(dt);
	sort_obj_by_distance(dt);
	calc_obj_height(dt);
	// rechercher ou afficher l'objet, cela correspond a sa distance entre la cam et le mur
	px_to_color = pt_set(data->ray->actual_ray, data->ray->wall_max + 1); // VALEUR PIXEL Y ????????
	while (px_to_color < obj_height)
	{
		pt_to_tex(px_to_color, data->m_img, get_pixel);
		px_to_color.y++;
	}
}
/*
void            display_column(t_data *data)
{
    data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
	ft_ciel_sol(data);
    display_ceiling(data);
    display_wall(data);
}*/
