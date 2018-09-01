#include "event.h"
#include "raycast.h"

void	move(t_data *data)
{
	check_move(data);
	if (data->walking == MOVE_UP)
		move_foreward(data);
	else if (data->walking == MOVE_DOWN)
		move_backward(data);
	else if (data->walking == MOVE_LEFT)
		move_left(data);
	else if (data->walking == MOVE_RIGHT)
		move_right(data);
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
	t_ptfl		wall_h;
	t_ptfl		wall_v;
	t_ptfl		dist;

	data->walking = MOVE_UP;
	cam = data->cam;
	rad = deg_to_rad(cam->theta);
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * 15);
	play_walk_song(data);
	new_pos.y = cam->crd_real->y - (int)(sinf(rad) * 15);
	wall_h = ptfl_set(0.0, 0.0);
	wall_v = ptfl_set(0.0, 0.0);
    if ((cam->theta > 0 && cam->theta < 90) || (cam->theta > 270))
        wall_h = horizon_right(data, cam->theta, 1);
    else if (cam->theta >= 90 && cam->theta < 270)
        wall_h = horizon_left(data, cam->theta, 1);
    /* Check vertical */
    if (cam->theta >= 0 && cam->theta < 180)
        wall_v = vertical_up(data, cam->theta, 1);
    else if (cam->theta >= 180)
        wall_v = vertical_down(data, cam->theta, 1);
    dist.x = return_distance(*cam->crd_real, wall_h);
    dist.y = return_distance(*cam->crd_real, wall_v);
    //printf("wall_v.x = %f .y = %f \nwall_h.x = %f y = %f \n", wall_v.x, wall_v.y, wall_h.x, wall_h.y);
    //printf("dist horizontal %f vertical %f\n", dist.x, dist.y);
	if (dist.x < 20.0 && dist.y > 20.0)
		{
			cam->crd_real->x = new_pos.x;
			printf("--- only x --- \n");
		}
	else if (dist.x > 20.0 && dist.y < 20.0)
	{
		printf("--- only y --- \n");
		cam->crd_real->y = new_pos.y;
	}
	else if (dist.y > 20.0 && dist.y > 20.0)
	{
		cam->crd_real->x = new_pos.x;
		cam->crd_real->y = new_pos.y;
	}
	set_real_to_map(cam->crd_real, cam->crd_map);
	loop(data);
	//printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

void	move_backward(t_data *data)
{
	t_cam		*cam;
	float		rad;

	data->walking = MOVE_DOWN;
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
	//printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

void	move_left(t_data *data)
{
	t_cam		*cam;
	float		theta;
	float		rad;
	t_point		new_pos;

	data->walking = MOVE_LEFT;
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
	//printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

void	move_right(t_data *data)
{
	t_cam		*cam;
	float		theta;
	float		rad;
	t_point		new_pos;

	data->walking = MOVE_RIGHT;
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
	//printf("theta = %f real x = %d y = %d, mapx = %d y = %d\n", cam->theta, cam->crd_real->x, cam->crd_real->y, cam->crd_map->x, cam->crd_map->y);
}

