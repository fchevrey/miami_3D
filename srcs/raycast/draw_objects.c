
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
		dt->obj_ar[i].coord[RAY_TO_DRAW].obj_dist = sqrt(pow((dt->obj_ar[i].obj_pt.x - dt->cam->crd_real->x),2) + pow((dt->obj_ar[i].obj_pt.y - dt->cam->crd_real->y), 2));
		i++;
	printf("obj_dist INSIDER %f, obj_pt.x = %f, obj_pt.y = %f\n", dt->obj_ar[i].obj_dist, dt->obj_ar[i].obj_pt.x, dt->obj_ar[i].obj_pt.y);
	}
	printf("obj_dist : %f\n", dt->obj_ar[i].obj_dist);
}

static void		calc_obj_height(t_data *dt)
{
	int			i;

	i = 0;
	while (dt->obj_ar[i].content != -1)
	{
		dt->obj_ar[i].obj_height = dt->cam->len_cam * (OBJ_H
				/ dt->obj_ar[i].obj_dist);
		i++;
	}
	printf("obj_height : %f\n",dt->obj_ar[i].obj_height);
}

static void		calc_obj_depth(t_data *dt)
{
	int			i;
//	float		min;
	float		scale;

	i = 0;
	while (dt->obj_ar[i].content != -1)
	{
		scale = dt->obj_ar[i].obj_dist / dt->obj_ar[i].wall_dist;
	printf("obj_wall_dist : %f\n",dt->obj_ar[i].wall_dist);
//		min = dt->ray->wall_max + (dt->ray->wall_min * scale);
		dt->obj_ar[i].obj_depth = dt->ray_ar[dt->obj_ar[i].ray_nb]->wall_max + (dt->ray_ar[dt->obj_ar[i].ray_nb]->wall_min * scale);
		i++;
	}
	printf("obj_depth : %f\n",dt->obj_ar[i].obj_depth);
}

void			display_objects(t_data *dt)
{
	t_point		px_to_color;
	int			i;
	int			height;
	int			width;
	i = 0;
	calc_obj_distance(dt);
	sort_obj_by_distance(dt);
	calc_obj_height(dt);
	calc_obj_depth(dt);// recherche ou afficher l'objet, cela correspond a sa distance entre la cam et le mur, c'est a dire sa profondeur
	px_to_color = pt_set(dt->obj_ar[i].ray_nb, /*pt_set(dt->obj_ar[i].obj_depth - dt->obj_ar[i].obj_height,*/ dt->ray_ar[dt->obj_ar[i].ray_nb]->wall_max + 1); // VALEUR PIXEL Y ????????
	height = px_to_color.y + dt->obj_ar[i].obj_height;
	width = px_to_color.x + dt->obj_ar[i].obj_width;
	printf("obj_width = %f\n" ,dt->obj_ar[i].obj_width);
	while (dt->obj_ar[i].content != -1)
	{
		printf("numero d'objet : %d, content d'object : %d\n",i ,dt->obj_ar[i].content);
		printf("px_to_color.x = %d; px_to_color.y = %d ; obj_height = %f\n", px_to_color.x, px_to_color.y, dt->obj_ar[i].obj_height);
		height = px_to_color.y + dt->obj_ar[i].obj_height;
		width = px_to_color.x + dt->obj_ar[i].obj_width;
		while(px_to_color.y < height)
		{
			px_to_color.x = dt->obj_ar[i].ray_nb;
			while (px_to_color.x < width)
			{
				pt_to_tex(px_to_color, dt->m_img, 0x00EE82EE);//get_pixel());
				px_to_color.x++;
			}
			px_to_color.y++;
		}
		i++;
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
