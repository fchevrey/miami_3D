
#include "main.h"
#include "raycast.h"

void				return_pos_map(int x, int y, int *x_map, int *y_map)
{
	*x_map = x / SIZE_GRID;
	*y_map = y / SIZE_GRID;
}

static float		return_distance(t_point a, t_point b)
{
	return (sqrt(pow((b.x - a.x),2) + pow((b.y - a.y), 2)));
}

/* 
** deg > 0 && deg < 90 || deg > 270
*/

t_point				horizon_right(t_data *data, float deg)
{
	t_point		point;
	float		ya;
	float		xa;
	int			x_map;
	int			y_map;

	ya = (deg > 0 && deg < 90) ? -SIZE_GRID : SIZE_GRID;
	xa = SIZE_GRID / tan(deg_to_rad(deg));
    if (xa < 0)
        xa = -xa;
	if (deg > 0 && deg < 90)
		point.y = data->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 1;
	else
		point.y = (data->cam->crd_real->y / SIZE_GRID) * SIZE_GRID + SIZE_GRID;
	point.x = data->cam->crd_real->x + (data->cam->crd_real->y - point.y) / tan(deg_to_rad(deg));
	return_pos_map(point.x, point.y, &x_map, &y_map);
	if (!is_in_map(x_map, y_map, data))
		return (point);
	while (data->map[y_map][x_map]->content == 0)
	{
		point.y += ya;
		point.x += xa;
		return_pos_map(point.x, point.y, &x_map, &y_map);
		if (!is_in_map(x_map, y_map, data))
			return (point);
	}
	return (point);
}

/*
** deg > 90 && deg < 270
*/

t_point				horizon_left(t_data *data, float deg)
{
	t_point		point;
	float		ya;
	float		xa;
	int			x_map;
	int			y_map;

	ya = (deg > 90 && deg < 180) ? -SIZE_GRID : SIZE_GRID;
	xa = SIZE_GRID / tan(deg_to_rad(deg));
    if (xa > 0)
        xa = -xa;
	if (deg > 90 && deg < 180)
		point.y = data->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 1;
	else
		point.y = (data->cam->crd_real->y / SIZE_GRID) * SIZE_GRID + SIZE_GRID;
	point.x = data->cam->crd_real->x + (data->cam->crd_real->y - point.y) / tan(deg_to_rad(deg));
	return_pos_map(point.x, point.y, &x_map, &y_map);
	if (!is_in_map(x_map, y_map, data))
		return (point);
	while (data->map[y_map][x_map]->content == 0)
	{
		point.y += ya;
		point.x += xa;
		return_pos_map(point.x, point.y, &x_map, &y_map);
		if (!is_in_map(x_map, y_map, data))
			return (point);
	}
	return (point);
	//return (return_distance(*data->cam->crd_real, point));
}

/*
** deg > 0 && deg < 180
*/

t_point				vertical_up(t_data *data, float deg)
{
	t_point     point;
	double		ya;
	double		xa;
	int			x_map;
	int			y_map;

	xa = (deg < 90) ? SIZE_GRID : -SIZE_GRID;
	ya = (SIZE_GRID * tan(deg_to_rad(deg))) * -1;
    if (ya > 0)
        ya = -ya;
	if (deg > 90)
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 1;
	else
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID;
	point.y = data->cam->crd_real->y + (data->cam->crd_real->x - point.x) * tan(deg_to_rad(deg));
	x_map = y_map = 0;
	return_pos_map(point.x, point.y, &x_map, &y_map);
	if (!is_in_map(x_map, y_map, data))
		return (point);
	while (data->map[y_map][x_map]->content == 0)
	{
		point.y += ya;
		point.x += xa;
		return_pos_map(point.x, point.y, &x_map, &y_map);
		if (!is_in_map(x_map, y_map, data))
			return (point);
	}
	return (point);
	//return (return_distance(*data->cam->crd_real, point));
}

/*
** deg > 180 && deg < 360
*/

t_point				vertical_down(t_data *data, float deg)
{
	t_point     point;
	double		ya;
	double		xa;
	int			x_map;
	int			y_map;

	xa = (deg > 270) ? SIZE_GRID : -SIZE_GRID;
	ya = SIZE_GRID * tan(deg_to_rad(deg));
    if (ya < 0)
        ya = -ya;
	if (deg < 270)
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 1;
	else
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID;
	point.y = data->cam->crd_real->y + (data->cam->crd_real->x - point.x) * tan(deg_to_rad(deg));
	x_map = y_map = 0;
	return_pos_map(point.x, point.y, &x_map, &y_map);
	if (!is_in_map(x_map, y_map, data))
		return (point);
	while (data->map[y_map][x_map]->content == 0)
	{
		point.y += ya;
		point.x += xa;
		return_pos_map(point.x, point.y, &x_map, &y_map);
		if (!is_in_map(x_map, y_map, data))
			return (point);
	}
	return (point);
	//return (return_distance(*data->cam->crd_real, point));
}

float			cast_ray(float deg, t_data *data, int *offset)
{
	t_point		hori;
	t_point		verti;
	float		dist_h;
	float		dist_v;

	hori = pt_set(0, 0);
	verti = hori;
    /* init a -1 si jamais je passe que sur les  4 premier if */
    dist_h = -1; // le x correspond a la distance horizontale
    dist_v = -1; // le y correspond a la distance verticale
    /* Cas particuliers */
    /*if (deg == 0)
        printf("deg ATTENTION\n");
    else if (deg == 90)
        printf("deg ATTENTION\n");
    else if (deg == 180)
        printf("deg ATTENTION\n");
    else if (deg == 270)
        printf("deg ATTENTION\n");*/
    /* Check horizon */
    if ((deg > 0 && deg < 90) || (deg > 270))
        hori = horizon_right(data, deg);
    else if (deg > 90 && deg < 270)
        hori = horizon_left(data, deg);
    /* Check vertical */
    if (deg > 0 && deg < 180)
        verti = vertical_up(data, deg);
    else if (deg > 180)
        verti = vertical_down(data, deg);
	dist_h = return_distance(*data->cam->crd_real, hori);
	dist_v = return_distance(*data->cam->crd_real, verti);
    /* Choisi la distance la plus petite */
    //printf("deg : %f dist_h %f dist_v %f\n",deg,  dist_h, dist_v);
	*offset = set_offset(hori, verti, dist_h, dist_v);
    if (dist_h < 0 || dist_v < dist_h)
        return (dist_v);
//    else if (dist_v < 0 || dist_h < dist_v)
	return (dist_h);
}
