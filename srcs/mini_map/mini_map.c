
#include "main.h"

// pt_to_tex((t_point){j, i}, data->m_img, get_color(0, 140, 85, 0));

void		draw_square_color(t_point up, t_point down, t_data *data, int color)
{
	int x;
	int y;

	y = up.y;
	while (y < down.y)
	{
		x = up.x;
		while (x < down.x)
		{
			pt_to_tex((t_point){x, y}, data->hud, color);
			x++;
		}
		y++;
	}
}

void		draw_mini_map(t_data *data)
{
	t_point up;
	t_point down;
	int 	y;
	int 	x;
	int		y_tab;
	int		x_tab;
	// boucle sur la map et va print les carré
	y = 0;
	y_tab = 0;
	while (y_tab <= data->ymax)
	{
		x_tab = 0;
		x = data->hud->size.x - 210;
		while (x_tab <= data->xmax)
		{
			up.x = x;
			up.y = y;
			down.x = x + 200 / data->xmax;
			down.y = y + 200 / data->ymax;
			if (data->map[y_tab][x_tab]->content == 1)
				draw_square_color(up, down, data, get_color(125, 255, 0, 0));
			else if (data->map[y_tab][x_tab]->content == 0)
				draw_square_color(up, down, data, get_color(125, 125, 125, 0));
			if (x_tab == data->cam->crd_map->x && y_tab == data->cam->crd_map->y)
				draw_square_color(up, down, data, get_color(125, 0, 0, 255));
			x += 200 / data->xmax;
			x_tab++;
		}
		y_tab++;
		y += 200 / data->ymax;
	}
}

void		mini_map(t_data *data)
{
	// fct qui va dessiner la map avec mur et vide
	draw_mini_map(data);

	// fct qui va dessiner sur la map les objet/player

}
