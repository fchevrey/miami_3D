
#include "main.h"
#include "raycast.h"

void				return_pos_map(float x, float y, float *x_map, float *y_map)
{
	*x_map = (x / SIZE_GRID);
	*y_map = (y / SIZE_GRID);
}

float				return_distance(t_point a, t_ptfl b)
{
	return (sqrt(pow((b.x - a.x),2) + pow((b.y - a.y), 2)));
}

static void			reinitialize_obj_ar_values(t_data *dt)
{
	int i;

	i = 0;
	while (dt->obj_ar[i].content != -1.0)
	{
		dt->obj_ar[i].obj_pt = ptfl_set(-1.0, -1.0);
		dt->obj_ar[i].obj_pt_map = pt_set(-1, -1);
		dt->obj_ar[i].content = -1.0;
		dt->obj_ar[i].x = -1.0;
		dt->obj_ar[i].obj_dist = -1.0;
		dt->obj_ar[i].wall_dist = -1.0;
		dt->obj_ar[i].obj_height = -1.0;
		dt->obj_ar[i].obj_depth = -1.0;
		dt->obj_ar[i].obj_width = -1.0;
		dt->obj_ar[i].ray_nb = -1.0;
		i++;
	}
}

static void			check_for_objects(t_data *dt, t_ptfl point, t_ptfl map)
{
	int				i;

	i = 0;
	if (dt->ray_ar[dt->act_ray] == 0)
		reinitialize_obj_ar_values(dt);
	if (dt->map[(int)map.y][(int)map.x]->content == 2)
	{
		while (dt->obj_ar[i].content != -1.0)
			i++;
		if (i == 0)
		{
			dt->obj_ar[i].obj_pt = point;
			dt->obj_ar[i].obj_pt_map = pt_set((int)map.x, (int)map.y);
			dt->obj_ar[i].content = dt->map[(int)map.y][(int)map.x]->content;
			dt->obj_ar[i].ray_nb = dt->act_ray;
			dt->obj_ar[i].obj_width += 1;
		}
		else if ((i > 0) && (((int)map.x != (int)dt->obj_ar[i - 1].obj_pt_map.x) || (int)map.y != (int)dt->obj_ar[i - 1].obj_pt_map.y))
		{
			dt->obj_ar[i].obj_pt = point;
			dt->obj_ar[i].obj_pt_map = pt_set((int)map.x, (int)map.y);
			dt->obj_ar[i].content = dt->map[(int)map.y][(int)map.x]->content;
			dt->obj_ar[i].ray_nb = dt->act_ray;
			dt->obj_ar[i].obj_width += 1;
		}
		else
			dt->obj_ar[i].obj_width += 1;
	}
}

/* 
** deg > 0 && deg < 90 || deg > 270
*/

t_ptfl				look_for_collision(t_ptfl point, t_data *dt, t_ptfl coeff)
{
	t_ptfl			map;

	map = ptfl_set(-1.0, -1.0);
	return_pos_map(point.x, point.y, &map.x, &map.y);
	if (!is_in_map(map.x, map.y, dt))
		return (point);
	while (dt->map[(int)map.y][(int)map.x]->content == 0
			|| dt->map[(int)map.y][(int)map.x]->content == 2)
	{
		check_for_objects(dt, point, map);
		point.y += coeff.y;
		point.x += coeff.x;
		return_pos_map(point.x, point.y, &map.x, &map.y);
		if (!is_in_map(map.x, map.y, dt))
			return (point);
	}
	return (point);
}

void				horizon_right(t_data *dt, float deg)
{
//	ft_putstr("HORIZON RIGHT DEBUT\n");
	t_ptfl		point;
	t_ptfl		coeff;

	coeff.y = (deg > 0 && deg < 90) ? -SIZE_GRID : SIZE_GRID;
	coeff.x = SIZE_GRID / tan(deg_to_rad(deg));
    if (coeff.x < 0)
        coeff.x = -coeff.x;
	if (deg > 0 && deg < 90)
		point.y = dt->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 0.0001;
	else
	{
		point.y = (dt->cam->crd_real->y / SIZE_GRID) * SIZE_GRID
			+ SIZE_GRID + 0.0001;
	}
	point.x = dt->cam->crd_real->x + (dt->cam->crd_real->y - point.y) 
		/ tan(deg_to_rad(deg));
	dt->ray_ar[dt->act_ray]->coeff_h = coeff;
	dt->ray_ar[dt->act_ray]->hori = look_for_collision(point, dt, coeff);
}

/*
** deg > 90 && deg < 270
*/

void				horizon_left(t_data *dt, float deg)
{
//	ft_putstr("HORIZON LEFT DEBUT\n");
	t_ptfl		point;
	t_ptfl		coeff;

	coeff.y = (deg > 90 && deg < 180) ? -SIZE_GRID : SIZE_GRID;
	coeff.x = SIZE_GRID / tan(deg_to_rad(deg));
    if (coeff.x > 0)
        coeff.x = -coeff.x;
	if (deg > 90 && deg < 180)
		point.y = dt->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 0.0001;
	else
	{
		point.y = (dt->cam->crd_real->y / SIZE_GRID) * SIZE_GRID
			+ SIZE_GRID + 0.0001;
	}
	point.x = dt->cam->crd_real->x + (dt->cam->crd_real->y - point.y)
		/ tan(deg_to_rad(deg));
	dt->ray_ar[dt->act_ray]->coeff_h = coeff;
	dt->ray_ar[dt->act_ray]->hori = look_for_collision(point, dt, coeff);
}

/*
** deg > 0 && deg < 180
*/

void				vertical_up(t_data *dt, float deg)
{
//	ft_putstr("VERTICAL UP DEBUT\n");
	t_ptfl     point;
	t_ptfl     coeff;

	coeff.x = (deg < 90) ? SIZE_GRID : -SIZE_GRID;
	coeff.y = (SIZE_GRID * tan(deg_to_rad(deg))) * -1;
    if (coeff.y > 0)
        coeff.y = -coeff.y;
	if (deg > 90)
		point.x = dt->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 0.0001;
	else
		point.x = dt->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID + 0.0001;
	point.y = dt->cam->crd_real->y + (dt->cam->crd_real->x - point.x)
		* tan(deg_to_rad(deg));
	dt->ray_ar[dt->act_ray]->coeff_v = coeff;
	dt->ray_ar[dt->act_ray]->verti = look_for_collision(point, dt, coeff);
}


/*
** deg > 180 && deg < 360
*/

void				vertical_down(t_data *dt, float deg)
{
//	ft_putstr("VERTICAL DOWN DEBUT\n");
	t_ptfl     point;
	t_ptfl     coeff;

	coeff.x = (deg > 270) ? SIZE_GRID : -SIZE_GRID;
	coeff.y = SIZE_GRID * tan(deg_to_rad(deg));
    if (coeff.y < 0)
        coeff.y = -coeff.y;
	if (deg < 270)
		point.x = dt->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 0.0001;
	else
		point.x = dt->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID;
	point.y = dt->cam->crd_real->y + (dt->cam->crd_real->x - point.x)
		* tan(deg_to_rad(deg));
	dt->ray_ar[dt->act_ray]->coeff_v = coeff;
	dt->ray_ar[dt->act_ray]->verti = look_for_collision(point, dt, coeff);
}

int				set_FLOAToffset(t_ptfl hori, t_ptfl verti, float dist_h, float dist_v)
{
	int			offset;;

	offset = 0;
	if (dist_v < 0 || dist_h < dist_v)
		offset = hori.x;
	else if (dist_h < 0 || dist_h > dist_v)
		offset = verti.y;
	offset = offset % 64;
	return (offset);
}
/*
static t_ptfl				special_cases(t_data *data, float deg)
{
	t_ptfl     point;
	double		ya;
	double		xa;
//	int			x_map;
//	int			y_map;
	xa = 0;
	ya = 0;
	if (deg >= 0.0 && deg <= 0.5)
	{
		xa = 64;
		point.x = data->cam->crd_map->x * SIZE_GRID;// + 64;
		point.y = data->cam->crd_real->y;
	}
	else if (deg >= 89.99 && deg <= 90.5)
	{
		ya = -64;
		point.x = data->cam->crd_real->x;
		point.y = data->cam->crd_map->y * SIZE_GRID;// - 1;
	}
	else if (deg >= 179.99 && deg <= 180.5)
	{
		xa = -64;
		point.x = data->cam->crd_map->x * SIZE_GRID;// -1;
		point.y = data->cam->crd_real->y;
	}
    else
	//else if (deg >= 269.99 && deg <= 270.5)
	{
		ya = 64;
		point.y = data->cam->crd_map->y * SIZE_GRID;// + 64;
		point.x = data->cam->crd_real->x;
	}
	return (look_for_collision(point, data, xa, ya));
}*/

void			cast_ray(t_data *dt, t_ray *act_ray)
{
	act_ray->hori = ptfl_set(0.0, 0.0);
	act_ray->verti = ptfl_set(0.0, 0.0);
    /* init a -1 si jamais je passe que sur les  4 premier if */
	act_ray->dist_h = -1;
	act_ray->dist_v = -1;
/*    if ((dt->ray->deg >= 89.99 && dt->ray->deg < 90.5) || (dt->ray->deg >= 269.99 && dt->ray->deg < 270.5))
	{
		dt->ray->verti = special_cases(dt, dt->ray->deg);
		return (dt->ray->dist_v = return_distance(*dt->cam->crd_real, dt->ray->verti));
	}
    if ((dt->ray->deg >= 0.0 && dt->ray->deg < 0.5) || (dt->ray->deg >= 179.99 && dt->ray->deg < 180.5))
	{
		dt->ray->hori = special_cases(dt, dt->ray->deg);
		return (dt->ray->dist_h = return_distance(*dt->cam->crd_real, dt->ray->hori));
	}*/
//	ft_putstr("CAST RAY\n");
//	ft_putnbr(act_ray->deg);
    /* Check horizon */
    if ((act_ray->deg > 0 && act_ray->deg < 90) || (act_ray->deg > 270))
        horizon_right(dt, act_ray->deg);
    else if (act_ray->deg > 90 && act_ray->deg < 270)
        horizon_left(dt, act_ray->deg);
    /* Check vertical */
	if (act_ray->deg > 0 && act_ray->deg < 180)
        vertical_up(dt, act_ray->deg);
    else if (act_ray->deg > 180)
		vertical_down(dt, act_ray->deg);
	act_ray->dist_h = return_distance(*dt->cam->crd_real, act_ray->hori);
	act_ray->dist_v = return_distance(*dt->cam->crd_real, act_ray->verti);
    /* Choisi la distance la plus petite */
    if (act_ray->dist_h < 0 || act_ray->dist_v < act_ray->dist_h)
        act_ray->dist_w_d = act_ray->dist_v;
	else if (act_ray->dist_v < 0 || act_ray->dist_h < act_ray->dist_v)
        act_ray->dist_w_d = act_ray->dist_h;
	else
        act_ray->dist_w_d = act_ray->dist_h;
}
