#include "main.h"

void			fill_wall_tex_b_and_w_tiles(t_data *data)
{
	t_point		i;
	t_point		counter;

	ft_putstr("DEBUT FILL BLACK AND WHITE TILES\n");
	i.y = 0;
	counter = pt_set(0,0);
	while (i.y < data->b_and_w_tiles->size.y)
	{
		if (counter.y >= 16)
			counter.y = 0;
		i.x = 0;
		if (counter.y < 8)
		{
			while (i.x < data->b_and_w_tiles->size.x)
			{
				counter.x = 0;
				while (counter.x < 16)
				{
					if (counter.x < 8)
						pt_to_tex(i, data->b_and_w_tiles, 0);
					else
						pt_to_tex(i, data->b_and_w_tiles, 0x00FFFFFF);
					i.x++;
					counter.x++;
				}
			}
		}
		else
		{
			while (i.x < data->b_and_w_tiles->size.x)
			{
				counter.x = 0;
				while (counter.x < 16)
				{
					if (counter.x < 8)
						pt_to_tex(i, data->b_and_w_tiles, 0x00FFFFFF);
					else
						pt_to_tex(i, data->b_and_w_tiles, 0);
					i.x++;
					counter.x++;
				}
			}
		}
		i.y++;
		counter.y++;
	}
	ft_putstr("FIN FILL BLACK AND GREY TILES\n");
}

void			fill_wall_tex_b_and_g_tiles(t_data *data)
{
	t_point		i;
	t_point		counter;

	ft_putstr("DEBUT FILL BLUE AND GREY TILES\n");
	i.y = 0;
	counter = pt_set(0,0);
	while (i.y < data->b_and_g_tiles->size.y)
	{
		if (counter.y >= 16)
			counter.y = 0;
		i.x = 0;
		if (counter.y < 8)
		{
			while (i.x < data->b_and_g_tiles->size.x)
			{
				counter.x = 0;
				while (counter.x < 16)
				{
					if (counter.x < 8)
						pt_to_tex(i, data->b_and_g_tiles, 0x0082AFAE);
					else
						pt_to_tex(i, data->b_and_g_tiles, 0x00E3E3E3); //0x00E38585);
					i.x++;
					counter.x++;
				}
			}
		}
		else
		{
			while (i.x < data->b_and_g_tiles->size.x)
			{
				counter.x = 0;
				while (counter.x < 16)
				{
					if (counter.x < 8)
						pt_to_tex(i, data->b_and_g_tiles, 0x00E3E3E3);//0x00B5D2CF);
					else
						pt_to_tex(i, data->b_and_g_tiles, 0x0082AFAE);
					i.x++;
					counter.x++;
				}
			}
		}
		i.y++;
		counter.y++;
	}
	ft_putstr("FIN FILL BLUE AND GREY TILES\n");
}
/*
void	load_wall_tex(int tex, char *img_name)
{
	SDL_Surface		*image;

	image = IMG_ReadXPMFromArray(img_name);
	if(!image)
	{
		 printf("IMG_ReadXPMFromArray: %s\n", IMG_GetError());
	// handle error
	}
//int IMG_isXPM(SDL_RWops *src);
/// Test sample.xpm to see if it is a XPM
// SDL_RWops *rwop;
//  rwop=SDL_RWFromFile("sample.xpm", "rb");
//   if(IMG_isXPM(rwop))
//    printf("sample.xpm is a XPM file.\n");
//     else
//      printf("sample.xpm is not a XPM file, or XPM support is not available.\n");
}*/
