
#include "main.h"
#include "raycast.h"

void				return_pos_map(float x, float y, float *x_map, float *y_map)
{
	*x_map = (x / SIZE_GRID);
	*y_map = (y / SIZE_GRID);
}

float		return_distance(t_point a, t_ptfl b)
{
	return (sqrt(pow((b.x - a.x),2) + pow((b.y - a.y), 2)));
}

/* 
** deg > 0 && deg < 90 || deg > 270
*/

t_ptfl				look_for_collision(t_ptfl point, t_data *data, float xa, float ya)
{
	float			x_map;
	float			y_map;
	int				i;

	return_pos_map(point.x, point.y, &x_map, &y_map);
	if (!is_in_map(x_map, y_map, data))
		return (point);
	while (data->map[(int)y_map][(int)x_map]->content == 0)
	{
		i = 0;
		if (data->map[(int)y_map][(int)x_map]->content == 2)
		{
			while (data->obj_ar[i].obj_pt.x != -1.0)
				i++;
			data->obj_ar[i].obj_pt = point;
			data->obj_ar[i].content = data->map[(int)y_map][(int)x_map]->content;
		}
		point.y += ya;
		point.x += xa;
		return_pos_map(point.x, point.y, &x_map, &y_map);
		if (!is_in_map(x_map, y_map, data))
			return (point);
	}
	return (point);
}

t_ptfl				horizon_right(t_data *data, float deg)
{
	t_ptfl		point;
	float		ya;
	float		xa;

	ya = (deg > 0 && deg < 90) ? -SIZE_GRID : SIZE_GRID;
	xa = SIZE_GRID / tan(deg_to_rad(deg));
    if (xa < 0)
        xa = -xa;
	if (deg > 0 && deg < 90)
		point.y = data->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 0.001;
	else
		point.y = (data->cam->crd_real->y / SIZE_GRID) * SIZE_GRID + SIZE_GRID + 0.001;
	point.x = data->cam->crd_real->x + (data->cam->crd_real->y - point.y)
	/ tan(deg_to_rad(deg));
	return (look_for_collision(point, data, xa, ya));
}

/*
** deg > 90 && deg < 270
*/

t_ptfl				horizon_left(t_data *data, float deg)
{
	t_ptfl		point;
	float		ya;
	float		xa;

	ya = (deg > 90 && deg < 180) ? -SIZE_GRID : SIZE_GRID;
	xa = SIZE_GRID / tan(deg_to_rad(deg));
    if (xa > 0)
        xa = -xa;
	if (deg > 90 && deg < 180)
		point.y = data->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 0.001;
	else
		point.y = (data->cam->crd_real->y / SIZE_GRID) * SIZE_GRID + SIZE_GRID + 0.001;
	point.x = data->cam->crd_real->x + (data->cam->crd_real->y - point.y) / tan(deg_to_rad(deg));
	return (look_for_collision(point, data, xa, ya));
}

/*
** deg > 0 && deg < 180
*/

t_ptfl				vertical_up(t_data *data, float deg)
{
	t_ptfl     point;
	double		ya;
	double		xa;

	xa = (deg < 90) ? SIZE_GRID : -SIZE_GRID;
	ya = (SIZE_GRID * tan(deg_to_rad(deg))) * -1;
    if (ya > 0)
        ya = -ya;
	if (deg > 90)
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 0.001;
	else
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID + 0.001;
	point.y = data->cam->crd_real->y + (data->cam->crd_real->x - point.x) * tan(deg_to_rad(deg));
	return (look_for_collision(point, data, xa, ya));
}


/*
** deg > 180 && deg < 360
*/

t_ptfl				vertical_down(t_data *data, float deg)
{
	t_ptfl     point;
	double		ya;
	double		xa;

	xa = (deg > 270) ? SIZE_GRID : -SIZE_GRID;
	ya = SIZE_GRID * tan(deg_to_rad(deg));
    if (ya < 0)
        ya = -ya;
	if (deg < 270)
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 0.001;
	else
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID;
	point.y = data->cam->crd_real->y + (data->cam->crd_real->x - point.x) * tan(deg_to_rad(deg));
	return (look_for_collision(point, data, xa, ya));
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

float			cast_ray(t_data *dt)
{
	dt->ray->hori = (t_ptfl){0,0};
	dt->ray->verti = dt->ray->hori;
    /* init a -1 si jamais je passe que sur les  4 premier if */
    dt->ray->dist_h = -1;
    dt->ray->dist_v = -1;
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
    /* Check horizon */
    if ((dt->ray->deg > 0 && dt->ray->deg < 90) || (dt->ray->deg > 270))
        dt->ray->hori = horizon_right(dt, dt->ray->deg);
    else if (dt->ray->deg > 90 && dt->ray->deg < 270)
        dt->ray->hori = horizon_left(dt, dt->ray->deg);
    /* Check vertical */
    if (dt->ray->deg > 0 && dt->ray->deg < 180)
        dt->ray->verti = vertical_up(dt, dt->ray->deg);
    else if (dt->ray->deg > 180)
        dt->ray->verti = vertical_down(dt, dt->ray->deg);
	dt->ray->dist_h = return_distance(*dt->cam->crd_real, dt->ray->hori);
	dt->ray->dist_v = return_distance(*dt->cam->crd_real, dt->ray->verti);
    /* Choisi la distance la plus petite */
    if (dt->ray->dist_h < 0 || dt->ray->dist_v < dt->ray->dist_h)
        return (dt->ray->dist_v);
	else if (dt->ray->dist_v < 0 || dt->ray->dist_h < dt->ray->dist_v)
        return (dt->ray->dist_h);
	return (dt->ray->dist_h);
}
