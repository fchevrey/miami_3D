#include "event.h"

void	next_song(void *param, uint8_t *stream, int len)
{
	static int	i = 1;
	t_data		*data;

	if (!stream)
		len += 0;
	data = (t_data*)param;
	Mix_PlayMusic(data->musics[i], 1 );
	ft_putstr("pouet : ");
	ft_putnbrnl(len);
	i++;
	if (i > 4)
		i = 0;
}
void	next_song2()
{
	/*static int	i = 1;
	t_data		*data;

	if (!stream)
		len += 0;
	data = (t_data*)param;
	Mix_PlayMusic(data->musics[i], 1 );
	ft_putstr("pouet : ");
	ft_putnbrnl(len);
	i++;
	if (i > 4)
		i = 0;*/
	ft_putstr("bah c'est finis\n");
}

void	sound(t_data *data)
{
	static int	i = 0;
 
	if (Mix_PlayingMusic() == 1 ||!data || !data->sounds || !data->musics)
		return ;
	if (i > 3)
	{
		i = 0;
		/*Mix_PauseMusic();
		printf("Music stopped\n");
		return ;*/
	}
	if (data->musics)
	{
		printf("try to play song %d\n", i);
		if (Mix_PlayMusic(data->musics[i], 1 ) < 0)
		{	
			printf("error : %s\n", Mix_GetError());
		}
		//Mix_HookMusic(&next_song, data);
		//Mix_HookMusicFinished(&next_song2);
	}
	i++;
}
