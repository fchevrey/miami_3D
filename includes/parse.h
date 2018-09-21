#ifndef PARSE_H
# define PARSE_H

#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/*
** List
*/

void			        ft_add(int x, int y, int content, t_map **map);
t_map			        ***ft_fill_tab(t_parse parse, t_map **map);

/*
** Parse
*/
int						ft_parse(char *str, t_map **map, t_parse *parse);
int				        ft_lin_is_good(char *str);

/*
** Pars TGA
*/


typedef struct          s_header
{
	unsigned char		id_length;
	unsigned char		color_map_type;
	unsigned char		image_type;
	unsigned char		color_map_spec[5];
	unsigned char		image_spec[15];
	unsigned char		*image_data;
	short				x;
	short				y;
}                       t_header;

typedef union		u_fill
{
	short 			value;
	struct			s_val
	{
		unsigned char a;
		unsigned char b;
	}				val;
}					t_fill;

void			ft_load_texture(int *endian, char *str, t_texture *img);

unsigned char	*ft_decode_tga(int *endian, t_header *header, unsigned char *image);

/*
** Free
*/

void		            free_list(t_map **list);
void		            freetab(t_map ***list);

#endif
