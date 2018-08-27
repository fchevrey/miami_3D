
#include "main.h"

void				display_line_wall(t_data *data, float wall_size, int x, int offset)
{
    int				y;
    int				i;
	float			coeff;
    
	i = 0;
    y = WIN_HEIGHT / 2 - wall_size / 2;
	coeff  = (float)data->b_and_w_tiles->size.y / wall_size;
    while (i < wall_size)
    {
        pt_to_tex((t_point){x, y + i}, data->m_img, \
				get_pixel((t_point){offset,(int)(coeff * (float)i)},\
					data->b_and_w_tiles));
        i++;
    }
}

void        ft_ciel_sol(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < WIN_HEIGHT / 2)
    {
        j = 0;
        while (j < WIN_WIDTH)
        {
            pt_to_tex((t_point){j, i}, data->m_img, get_color(0, 0, 0, 240));
            j++;
        }
        i++;
    }
    while (i < WIN_HEIGHT)
    {
        j = 0;
        while (j < WIN_WIDTH)
        {
            pt_to_tex((t_point){j, i}, data->m_img, get_color(0, 140, 85, 0));
            j++;
        }
        i++;
    }
}
