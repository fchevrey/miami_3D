/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:28:56 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:09:07 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		on_error(char **name, int *nb)
{
	ft_error("error lading : ", *name, Mix_GetError());
	*nb = *nb - 1;
	ft_strdel(name);
	return (1);
}

static int		load_sound(t_data *data, char **songs)
{
	int			nb;
	int			i;
	char		*music_path;
	char		*name;

	nb = 0;
	while (songs[nb])
		nb++;
	i = 0;
	if (!(data->sounds = (Mix_Chunk**)malloc(sizeof(Mix_Chunk*) * (nb + 1))))
		return (-1);
	data->sounds[nb] = NULL;
	music_path = ft_strjoin(data->path, "assets/sounds/");
	while (i < nb)
	{
		name = ft_strjoin(music_path, songs[i]);
		if (!(data->sounds[i] = Mix_LoadWAV(name)) && on_error(&name, &nb) == 1)
			continue ;
		ft_strdel(&name);
		i++;
	}
	ft_strdel(&music_path);
	return (0);
}

static int		load_music(t_data *data, char **songs)
{
	int			nb;
	int			i;
	char		*music_path;
	char		*name;

	nb = 0;
	while (songs[nb])
		nb++;
	i = 0;
	if (!(data->musics = (Mix_Music**)malloc(sizeof(Mix_Music*) * (nb + 1))))
		return (-1);
	data->musics[nb] = NULL;
	music_path = ft_strjoin(data->path, "assets/sounds/");
	while (i < nb)
	{
		name = ft_strjoin(music_path, songs[i]);
		if (!(data->musics[i] = Mix_LoadMUS(name)) && on_error(&name, &nb) == 1)
			return (-1);
		ft_strdel(&name);
		i++;
	}
	ft_strdel(&music_path);
	return (nb);
}

int				sound_init(t_data *data)
{
	char		**songs;

	if (!(songs = ft_strsplit(
		"music01.wav\fmusic02.wav\fmusic03.wav\fmusic04.wav\fmusic05.wav",
		'\f')))
	{
		return (-1);
	}
	if ((data->len_music = load_music(data, songs)) < 0)
		return (-1);
	ft_tabdel(&songs);
	if (!data->musics)
		return (-1);
	if (!(songs = ft_strsplit("footstep_01.wav\floud_shot.wav", '\f')))
		return (-1);
	if ((load_sound(data, songs)) < 0)
		return (-1);
	ft_tabdel(&songs);
	if (!data->sounds)
		return (-1);
	Mix_VolumeMusic(60);
	return (1);
}
