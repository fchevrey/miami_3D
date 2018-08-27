#include "event.h"

void	move(t_data *data, int movement)
{
	if (movement == MOVE_UP)
		move_foreward(data);
	else if (movement == MOVE_DOWN)
		move_backward(data);
	//else if (movement == MOVE_LEFT)
	//else if (movement == MOVE_RIGHT)
}

static void		play_walk_song(t_data *data)
{
	//printf("walk channel = %d\n", data->walk_channel);
	if (data->walk_channel == -12)
		data->walk_channel = Mix_PlayChannel(-1, data->sounds[0], -1);
	else
		if (Mix_Paused(data->walk_channel) == 1)
			Mix_Resume(data->walk_channel);
}

void			move_foreward(t_data *data)
{
	t_cam		*cam;
	float		rad;
	t_point		new_pos;

	cam = data->cam;
	rad = deg_to_rad(cam->theta);
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * 15);
	play_walk_song(data);
	if (cam->theta < 54 || cam->theta > 306)
		new_pos.y = cam->crd_real->y + (int)(sinf(rad) * 15);
	else
		new_pos.y = cam->crd_real->y - (int)(sinf(rad) * 15);
	new_pos = check_collision(*cam->crd_real, new_pos, data);
	cam->crd_real->x = new_pos.x;
	cam->crd_real->y = new_pos.y;
	set_real_to_map(cam->crd_real, cam->crd_map);
	loop(data);
	printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

void	move_backward(t_data *data)
{
	t_cam		*cam;
	float		rad;

	cam = data->cam;
	rad = deg_to_rad(cam->theta);
	cam->crd_real->x -= (cosf(rad) * 15);
	//if (cam->theta < 90 || cam->theta > 270)
	//	cam->crd_real->y -= (int)(sinf(rad) * 10);
	//else
		cam->crd_real->y += (sinf(rad) * 15);
	set_real_to_map(cam->crd_real, cam->crd_map);
	play_walk_song(data);
	loop(data);
	printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

void	move_left(t_data *data)
{
	t_cam		*cam;
	float		theta;
	float		rad;
	t_point		new_pos;

	cam = data->cam;
	theta = cam->theta + 90;
	if (theta >= 360)
		theta -= 360;
	rad = deg_to_rad(theta);
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * 15);
	play_walk_song(data);
	if (theta < 54 || theta > 306)
		new_pos.y = cam->crd_real->y + (int)(sinf(rad) * 15);
	else
		new_pos.y = cam->crd_real->y - (int)(sinf(rad) * 15);
	new_pos = check_collision(*cam->crd_real, new_pos, data);
	cam->crd_real->x = new_pos.x;
	cam->crd_real->y = new_pos.y;
	set_real_to_map(cam->crd_real, cam->crd_map);
	loop(data);
	printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

void	move_right(t_data *data)
{
	t_cam		*cam;
	float		theta;
	float		rad;
	t_point		new_pos;

	cam = data->cam;
	theta = cam->theta - 90;
	if (theta < 0)
		theta += 360;
	rad = deg_to_rad(theta);
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * 15);
	play_walk_song(data);
	if (theta < 54 || theta > 306)
		new_pos.y = cam->crd_real->y + (int)(sinf(rad) * 15);
	else
		new_pos.y = cam->crd_real->y - (int)(sinf(rad) * 15);
	new_pos = check_collision(*cam->crd_real, new_pos, data);
	cam->crd_real->x = new_pos.x;
	cam->crd_real->y = new_pos.y;
	set_real_to_map(cam->crd_real, cam->crd_map);
	loop(data);
	printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

