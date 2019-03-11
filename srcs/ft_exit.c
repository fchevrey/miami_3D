/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <fchevrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:28:06 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 16:34:35 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "main.h"
#include "event.h"

static void		free_sounds(t_data *data)
{
	int		i;

	if (data->sounds)
	{
		i = 0;
		while (data->sounds[i])
		{
			Mix_FreeChunk((Mix_Chunk*)data->sounds[i]);
			data->sounds[i] = NULL;
			i++;
		}
		free(data->sounds);
		data->sounds = NULL;
	}
}

static void		free_music(t_data *data)
{
	int		i;

	if (data->musics)
	{
		i = 0;
		while (data->musics[i])
		{
			Mix_FreeMusic((Mix_Music*)data->musics[i]);
			data->musics[i] = NULL;
			i++;
		}
		free(data->musics);
		data->musics = NULL;
	}
	free_sounds(data);
	Mix_Quit();
}

void			ft_exit(t_data **data)
{
	if (!data || !*data)
		exit(1);
	free_music(*data);
	free_win(&(*data)->win);
	(*data)->win = NULL;
	free_tex(&(*data)->m_img);
	free_tex(&(*data)->hud);
	(*data)->m_img = NULL;
	free(*data);
	*data = NULL;
	SDL_Quit();
	ft_putstr("J'ai quitté proprement\n");
	exit(0);
}
