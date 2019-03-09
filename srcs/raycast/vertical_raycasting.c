#include "main.h"
#include "raycast.h"

static float		return_distance(t_point a, t_ptfl b)
{
	return (sqrt(pow((b.x - a.x),2) + pow((b.y - a.y), 2)));
}

/*
** deg > 0 && deg < 180
*/

static t_ptfl		vertical_up(t_data *data, float deg)
{
	t_ptfl			point;
	t_ptfl			coeff;

//printf("vertical up -- ");
	coeff.x = (deg < 90) ? SIZE_GRID : -SIZE_GRID;
	coeff.y = (SIZE_GRID * tan(deg_to_rad(deg))) * -1;
    if (coeff.y > 0)
        coeff.y = -coeff.y;
	if (deg > 90)
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID;// - 0.0001;
	else
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID;;// + SIZE_GRID;// + 0.00001;
    point.x += (point.x > data->cam->crd_real->x ) ? - 0.0001 : SIZE_GRID;
	point.y = data->cam->crd_real->y + (data->cam->crd_real->x - point.x) * tan(deg_to_rad(deg));
	
	return (check_walls(point, data, coeff));
}


/*
** deg > 180 && deg < 360
*/

static t_ptfl		vertical_down(t_data *data, float deg)
{
	t_ptfl			point;
	t_ptfl			coeff;

//printf("vertical down -- ");
	coeff.x = (deg > 270) ? SIZE_GRID : -SIZE_GRID;
	coeff.y = SIZE_GRID * tan(deg_to_rad(deg));
    if (coeff.y < 0)
        coeff.y = -coeff.y;
	if (deg < 270)
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID - 0.0001;
	else
		point.x = data->cam->crd_real->x / SIZE_GRID * SIZE_GRID + SIZE_GRID;
	point.y = data->cam->crd_real->y + (data->cam->crd_real->x - point.x) * tan(deg_to_rad(deg));
    point.x += (point.x > data->cam->crd_real->x ) ? - 0.0001 : SIZE_GRID;
//	printf("point.x = %f -- point.y = %f -- ", point.x, point.y);
	point = check_walls(point, data, coeff);
//	printf("point.x = %f -- point.y = %f -- ", point.x, point.y);
	return (point);
}

void              vertical_raycasting(t_data *dt)
{
    if (dt->ray->deg > 0 && dt->ray->deg < 180)
        dt->ray->verti = vertical_up(dt, dt->ray->deg);
    else if (dt->ray->deg > 180)
        dt->ray->verti = vertical_down(dt, dt->ray->deg);
	dt->ray->dist_v = return_distance(*dt->cam->crd_real, dt->ray->verti);
}