#include "event.h"
#include <stdlib.h>

static int		keypress_do_event(int key, t_data *data)
{
	static t_funar_keyb		*tab_fct = NULL;
	static int				size_tab;
	int						i;

	if (key == 400)
		return (1);
	if (tab_fct == NULL)
		tab_fct = fill_funar_key_press(&size_tab);
	i = 0;
	if (key == SDLK_ESCAPE)
	{
		free(tab_fct);
		return (-1);
	}
	while (i < size_tab)
	{
		if (tab_fct[i].key == key)
		{
			tab_fct[i].f(data);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		keyrelease_do_event(int key, t_data *data)
{
	static t_funar_keyb		*tab_fct = NULL;
	static int				size_tab;
	int						i;

	if (key == 400)
		return (1);
	if (tab_fct == NULL)
		tab_fct = fill_funar_key_release(&size_tab);
	i = 0;
	if (key == SDLK_ESCAPE)
	{
		free(tab_fct);
		return (-1);
	}
	while (i < size_tab)
	{
		if (tab_fct[i].key == key)
		{
			tab_fct[i].f(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int				ft_keyboard(int key, int repeat, SDL_Event *event, t_data *data)
{
	int			ret;

	if (key == SDLK_UP && repeat == 1)
		data->walking = MOVE_UP;
	else if (key == SDLK_DOWN && repeat == 1)
		data->walking = MOVE_DOWN;
	ret = 0;
	if (event->type == SDL_KEYDOWN)
	{
		if ((ret = keypress_do_event(key, data)) == 1)
			return (0);
	}
	else
		if ((ret = keyrelease_do_event(key, data)) == 1)
			return (0);
	if (ret == -1)
		ft_exit(&data);
	return (0);
}
