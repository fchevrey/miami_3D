/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:00:54 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/12 20:14:35 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	next_song(t_data *data)
{
	static int	i = 0;

	if (!data || !data->musics || !data->musics[i])
		return ;
	if (i >= data->len_music)
		i = 0;
	if (data->musics)
	{
		if (Mix_PlayMusic(data->musics[i], 1) < 0)
		{
			ft_error("error : \n", Mix_GetError(), NULL);
		}
	}
	i++;
}

void	play_walk_sound(t_data *data)
{
	if (!data->sounds || !data->sounds[0])
		return ;
	if (data->walk_channel == -12)
		data->walk_channel = Mix_PlayChannel(-1, data->sounds[0], -1);
	else
	{
		if (Mix_Paused(data->walk_channel) == 1)
			Mix_Resume(data->walk_channel);
	}
}

void	play_shot_sound(t_data *data)
{
	if (!data->sounds || !data->sounds[1])
		return ;
	Mix_PlayChannel(-1, data->sounds[1], 0);
}

void	sound(t_data *data)
{
	if (Mix_PlayingMusic() == 1 || !data || !data->sounds || !data->musics)
		return ;
	next_song(data);
}
