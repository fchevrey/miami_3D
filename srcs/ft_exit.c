/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <fchevrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:28:06 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:52:46 by fchevrey         ###   ########.fr       */
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

static void		free_all_texts(t_data *data)
{
	int i;

	i = 0;
	free_tex(&data->m_img);
	free_tex(&data->hud);
	while (i < WALL_TEXTS)
	{
		free_tex(&data->wall_texts[i]);
		i++;
	}
	free(data->wall_texts);
	data->wall_texts = NULL;
	i = 0;
	while (i < 3)
	{
		free_tex(&data->texts[i]);
		i++;
	}
	free(data->texts);
	data->texts = NULL;
}

static void		destroy_map(t_data *data)
{
	int		i;
	int		j;

	if (!data || !data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			free(data->map[i][j]);
			data->map[i][j] = NULL;
			j++;
		}
		free(data->map[i]);
		data->map[i] = NULL;
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void			ft_exit(t_data **data)
{
	if (!data || !*data)
		exit(1);
	free_all_texts(*data);
	free_music(*data);
	free_win(&(*data)->win);
	(*data)->win = NULL;
	(*data)->m_img = NULL;
	ft_strdel(&(*data)->path);
	free((*data)->cam->crd_map);
	free((*data)->cam->crd_real);
	free((*data)->cam);
	free((*data)->ray);
	destroy_map(*data);
	free(*data);
	*data = NULL;
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
