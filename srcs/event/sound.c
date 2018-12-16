/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:00:54 by fchevrey          #+#    #+#             */
/*   Updated: 2018/12/16 17:20:20 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	next_song(t_data *data)
{
	static int	i = 0;

	if (!data || !data->musics)
		return ;
	printf("lenmusic = %d\n", data->len_music);
	if (i >= data->len_music)
		i = 0;
	if (data->musics)
	{
		if (Mix_PlayMusic(data->musics[i], 1 ) < 0)
		{
			ft_error("error : \n", Mix_GetError(), NULL);
		}
	}
	i++;
}

void	sound(t_data *data)
{
 
	if (Mix_PlayingMusic() == 1 ||!data || !data->sounds || !data->musics)
		return ;
	next_song(data);
}
