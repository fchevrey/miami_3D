#include "main.h"
#include "raycast.h"

t_ptfl				horizon_right(t_data *data, float deg)
{
	t_ptfl		point;
	t_ptfl		coeff;

printf("horizon right -- ");
	coeff.y = (deg > 0 && deg < 90) ? -SIZE_GRID : SIZE_GRID;
	coeff.x = SIZE_GRID / tan(deg_to_rad(deg));
    if (coeff.x < 0)
        coeff.x = -coeff.x;
	if (deg > 0 && deg < 90)
		point.y = data->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 0.0001;
	else
		point.y = (data->cam->crd_real->y / SIZE_GRID) * SIZE_GRID + SIZE_GRID;// + 0.00001;
	point.x = data->cam->crd_real->x + (data->cam->crd_real->y - point.y)
	/ tan(deg_to_rad(deg));
	return (look_for_collision(point, data, coeff));
}

/*
** deg > 90 && deg < 270
*/

t_ptfl				horizon_left(t_data *data, float deg)
{
	t_ptfl		point;
	t_ptfl		coeff;

printf("horizon left -- ");
	coeff.y = (deg > 90 && deg < 180) ? -SIZE_GRID : SIZE_GRID;
	coeff.x = (float)SIZE_GRID / tanf(deg_to_rad(deg));
    if (coeff.x > 0)
        coeff.x = -coeff.x;
	if (deg > 90 && deg < 180)
		point.y = data->cam->crd_real->y / SIZE_GRID * SIZE_GRID - 0.0001;
	else
		point.y = (data->cam->crd_real->y / SIZE_GRID) * SIZE_GRID + SIZE_GRID;// + 0.0001;
	point.x = data->cam->crd_real->x + (data->cam->crd_real->y - point.y) / tan(deg_to_rad(deg));
//	printf("point.x = %f -- point.y = %f -- ", point.x, point.y);
	point = look_for_collision(point, data, coeff);
//	printf(" xa = %f ya = %f -- point.x = %f -- point.y = %f -- ", xa, ya, point.x, point.y);
	return (point);
}

void              horizontal_raycasting(t_data *dt, float deg)
{
    if ((dt->ray->deg > 0 && dt->ray->deg < 90) || (dt->ray->deg > 270))
        dt->ray->hori = horizon_right(dt, dt->ray->deg);
    else if (dt->ray->deg > 90 && dt->ray->deg < 270)
        dt->ray->hori = horizon_left(dt, dt->ray->deg);
    dt->ray->dist_h = return_distance(*dt->cam->crd_real, dt->ray->hori);
}