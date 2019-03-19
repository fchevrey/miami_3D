/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:40:58 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/14 11:05:09 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"
# include <fcntl.h>
# include <unistd.h>

t_point					find_start(t_map ***map);

/*
** List
*/

void					ft_add(int x, int y, int content, t_map **map);
t_map					***fill_map(t_parse parse, t_map **map, int nb_elem);

/*
** Parse
*/
int						ft_parse(char *str, t_map **map, t_parse *parse);
int						ft_lin_is_good(char *str);

/*
** Parse TGA
*/

typedef struct			s_header
{
	unsigned char		id_length;
	unsigned char		color_map_type;
	unsigned char		image_type;
	unsigned char		color_map_spec[5];
	unsigned char		image_spec[15];
	unsigned char		*image_data;
	short				x;
	short				y;
}						t_header;

typedef union			u_fill
{
	short				value;
	struct				s_val
	{
		unsigned char	a;
		unsigned char	b;
	}					val;
}						t_fill;

int						ft_load_texture(int *endian, char *str, t_texture *img);
unsigned char			*ft_decode_tga(int *endian, t_header *header,
		unsigned char *image);

/*
** Free
*/

void					free_list(t_map **list);
void					freetab(t_map ***list);
void					ft_free_exit(t_map **map, int fd, char *lin, int err);
void					malloc_failed(char *str);

#endif
