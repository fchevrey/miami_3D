#include "main.h"

static int		load_sound(t_data *data, char **songs)
{
	int			nb;
	int			i;
	char 		*music_path;
	char 		*name;

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
		if (!(data->sounds[i] = Mix_LoadWAV(name)))
			return (ft_error("error lading : ", name, Mix_GetError()));
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
	char 		*music_path;
	char 		*name;

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
		if (!(data->musics[i] = Mix_LoadMUS(name)))
			return (ft_error("error lading : ", name, Mix_GetError()));
				ft_strdel(&name);
		i++;
	}
	ft_strdel(&music_path);
	return (1);
}

int		sound_init(t_data *data)
{
	char		**songs;

	data->musics = NULL;
	data->sounds = NULL;
	if (!(songs = ft_strsplit("music01.wav\fmusic02.wav", '\f')))
		return (-1);
	load_music(data, songs);
	ft_tabdel(&songs);
	if (!data->musics)
		return (-1);
	if (!(songs = ft_strsplit("footstep_01.wav\floud_shot.wav", '\f')))
		return (-1);
	if (load_sound(data, songs) < 0)
		ft_putstr("sound loading error\n");
	ft_tabdel(&songs);
	if (!data->sounds)
		return (-1);
	return (1);
}

