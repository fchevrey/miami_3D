#include "event.h"
#include <stdlib.h>

/*static int		check_event(int key, int reapeat, int type, t_data *data)
{
	static t_funar_keyb		*tab_fct[3] = NULL;
	static int				size_tab[3];
	int						i;

	if (tab_fct[0] == NULL)
		tab_fct = fill_funar_key_press(&size_tab[0]);
	if (tab_fct[1] == NULL)
		tab_fct = fill_funar_key_release(&size_tab[1]);
	if (tab_fct[2] == NULL)
		tab_fct = fill_funar_key_repeat(&size_tab[2]);
	i = 0;
	if (key == SDLK_ESCAPE)
	{
		while (i < 3)
			free(tab_fct[i++]);
		return (-1);
	}
	if (type == KEY_PRESS)
		return (do_event());
	else 
		return (do_event(tab_fct[2], key, ));
}*/

static int		keypress_do_event(int key, int repeat, t_data *data)
{
	static t_funar_keyb		*tab_fct = NULL;
	static int				size_tab;
	int						i;

	if (tab_fct == NULL)
		tab_fct = fill_funar_keypress(&size_tab);
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
			if (tab_fct[i].f && (!repeat || tab_fct[i].repeat == repeat))
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

	if (tab_fct == NULL)
		tab_fct = fill_funar_keyrelease(&size_tab);
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
			if (tab_fct[i].f)
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

	ret = 0;
	if (event->type == SDL_KEYDOWN)
	{
		if ((ret = keypress_do_event(key, repeat, data)) == 1)
			return (0);
	}
	else if (event->type == SDL_KEYUP)
		if ((ret = keyrelease_do_event(key, data)) == 1)
			return (0);
	if (ret == -1)
	{
		keyrelease_do_event(key, data);
		ft_putstr("quitting...\n");
		ft_exit(&data);
	}
	return (0);
}
