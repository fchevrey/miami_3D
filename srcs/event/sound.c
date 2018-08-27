#include "event.h"

void	sound(t_data *data)
{
	static int	i = 0;

	if (!data || !data->sounds || !data->musics)
		return ;
	if (i > 1)
	{
		i = 0;
		Mix_PauseMusic();
		printf("Music stopped\n");
		return ;
	}
	if (data->musics)
	{
		printf("try to play song %d\n", i);
		if (Mix_PlayMusic(data->musics[i], 1 ) < 0)
			printf("error : %s\n", Mix_GetError());
	}
	i++;
}
