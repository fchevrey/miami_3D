
#include "event.h"

void	stand(t_data *data)
{
	data->cam->h_cam = 0.5;
	data->cam->len_cam = (WIN_WIDTH * data->cam->h_cam) / tan(deg_to_rad(FOV * data->cam->h_cam));
	rendering(data);
}

void	crouch(t_data *data)
{
	data->cam->h_cam = 0.9;
	data->cam->len_cam = (WIN_WIDTH * data->cam->h_cam) / tan(deg_to_rad(FOV * data->cam->h_cam));
	rendering(data);
}

void	jump(t_data *data)
{
	data->cam->h_cam = 0.3;
	data->cam->len_cam = (WIN_WIDTH * data->cam->h_cam) / tan(deg_to_rad(FOV * data->cam->h_cam));
	rendering(data);
}