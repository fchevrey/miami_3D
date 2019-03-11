#include "raycast.h"
#include <math.h>

int				set_offset(t_data *data, t_texture *img)
{
	if (data->ray->dist_v < 0 || data->ray->dist_h < data->ray->dist_v)
		data->ray->offset = (int)roundf(data->ray->hori.x) % img->size.x;
	else if (data->ray->dist_h < 0 || data->ray->dist_h > data->ray->dist_v)
		data->ray->offset = (int)roundf(data->ray->verti.y) % img->size.y;
	return (data->ray->offset);
}
