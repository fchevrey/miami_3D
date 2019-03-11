#include "event.h"

void	look_left_from_key(t_data *data)
{
	data->cam->theta += 10;
	if (data->cam->theta >= 360)
		data->cam->theta -= 360;
	//		data->cam->theta -= 360;
	//	printf("look left - theta = %f real x = %d y = %d, mapx = %d y = %d\n", 
	//	data->cam->theta, data->cam->crd_real->x, data->cam->crd_real->y, data->cam->crd_map->x, data->cam->crd_map->y);
	//printf("theta = %f\n", data->cam->theta);
	rendering(data);
}

void	look_right_from_key(t_data *data)
{
	data->cam->theta -= 10;
	if (data->cam->theta < 0)
		data->cam->theta += 360;
	//printf("look right - theta = %f real x = %d y = %d, mapx = %d y = %d\n", 
	//data->cam->theta, data->cam->crd_real->x, data->cam->crd_real->y, data->cam->crd_map->x, data->cam->crd_map->y);
	rendering(data);
}
