/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:00:00 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/12 19:57:35 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "raycast.h"

void	move(t_data *data, float deltatime)
{
	const int speed = 50;

	check_move(data);
	if (data->walking == MOVE_UP)
		move_foreward(data, deltatime, speed);
	else if (data->walking == MOVE_DOWN)
		move_backward(data, deltatime, speed);
	else if (data->walking == MOVE_LEFT)
		move_left(data, deltatime, speed);
	else if (data->walking == MOVE_RIGHT)
		move_right(data, deltatime, speed);
}
static void		apply_real_move(t_data *data, t_ptfl wall_h, t_ptfl wall_v,
		t_point new_pos)
{
	t_ptfl		dist;
	t_cam		*cam;

	cam = data->cam;
	dist.x = return_distance(*cam->crd_real, wall_h);
	dist.y = return_distance(*cam->crd_real, wall_v);
	if (dist.x < 20.0 && dist.y > 20.0)
		cam->crd_real->x = new_pos.x;
	else if (dist.x > 20.0 && dist.y < 20.0)
		cam->crd_real->y = new_pos.y;
	else if (dist.y > 20.0 && dist.y > 20.0)
	{
		cam->crd_real->x = new_pos.x;
		cam->crd_real->y = new_pos.y;
	}
	set_real_to_map(cam->crd_real, cam->crd_map);
	rendering(data);
}

void	move_foreward(t_data *data, float deltatime, const int speed)
{
	t_cam		*cam;
	float		rad;
	t_point		new_pos;
	t_ptfl		wall_h;
	t_ptfl		wall_v;

	data->walking = MOVE_UP;
	cam = data->cam;
	rad = deg_to_rad(cam->theta);
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * speed * deltatime);
	play_walk_sound(data);
	new_pos.y = cam->crd_real->y - (int)(sinf(rad) * speed * deltatime);
	if ((cam->theta > 0 && cam->theta < 90) || (cam->theta > 270))
		wall_h = horizon_right(data, cam->theta);
	else
		wall_h = horizon_left(data, cam->theta);
	if (cam->theta >= 0 && cam->theta < 180)
		wall_v = vertical_up(data, cam->theta);
	else
		wall_v = vertical_down(data, cam->theta);
	apply_real_move(data, wall_h, wall_v, new_pos);
}

void	move_backward(t_data *data, float deltatime, const int speed)
{
	float		rad;
	t_point		new_pos;
	t_ptfl		wall_h;
	t_ptfl		wall_v;
	float		theta;

	data->walking = MOVE_DOWN;
	theta = data->cam->theta + 180;
	if (theta >= 360)
		theta -= 360;
		rad = deg_to_rad(data->cam->theta);
	new_pos.x = data->cam->crd_real->x - (int)(cosf(rad) * speed * deltatime);
	new_pos.y = data->cam->crd_real->y + (int)(sinf(rad) * speed * deltatime);
	if ((theta > 0 && theta < 90) || (theta > 270))
		wall_h = horizon_right(data, theta);
	else
		wall_h = horizon_left(data, theta);
	if (theta >= 0 && theta < 180)
		wall_v = vertical_up(data, theta);
	else
		wall_v = vertical_down(data, theta);
	apply_real_move(data, wall_h, wall_v, new_pos);
}

void	move_left(t_data *data, float deltatime, const int speed)
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
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * speed * deltatime);
	play_walk_sound(data);
	if (theta < 54 || theta > 306)
		new_pos.y = cam->crd_real->y + (int)(sinf(rad) * speed * deltatime);
	else
		new_pos.y = cam->crd_real->y - (int)(sinf(rad) * speed * deltatime);
	//new_pos = check_collision(*cam->crd_real, new_pos, data);
	cam->crd_real->x = new_pos.x;
	cam->crd_real->y = new_pos.y;
	set_real_to_map(cam->crd_real, cam->crd_map);
	rendering(data);
}

void	move_right(t_data *data, float deltatime, const int speed)
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
	new_pos.x = cam->crd_real->x + (int)(cosf(rad) * speed * deltatime);
	play_walk_sound(data);
	if (theta < 54 || theta > 306)
		new_pos.y = cam->crd_real->y + (int)(sinf(rad) * speed * deltatime);
	else
		new_pos.y = cam->crd_real->y - (int)(sinf(rad) * speed * deltatime);
	//new_pos = check_collision(*cam->crd_real, new_pos, data);
	cam->crd_real->x = new_pos.x;
	cam->crd_real->y = new_pos.y;
	set_real_to_map(cam->crd_real, cam->crd_map);
	rendering(data);
}
