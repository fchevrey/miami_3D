/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tga.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:57:28 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:43:21 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int				ft_fill_header(t_header *header, int fd)
{
	char	buff[18];
	int		i;

	if (read(fd, buff, 18) < 18)
		return (-1);
	header->id_length = (unsigned char)buff[0];
	header->color_map_type = (unsigned char)buff[1];
	header->image_type = (unsigned char)buff[2];
	i = 2;
	while (i < 18)
	{
		if (i < 8)
			header->color_map_spec[i - 3] = (unsigned char)buff[i];
		else
			header->image_spec[i - 8] = (unsigned char)buff[i];
		i++;
	}
	return (0);
}

static unsigned char	*ft_init_image(int fd, t_header *header)
{
	unsigned char	*image;
	int				size;
	int				rd;

	image = NULL;
	size = (header->x) * (header->y) * 4;
	if (!(image = (unsigned char *)malloc(sizeof(unsigned char) * size + 1)))
		malloc_failed("tga image\n");
	rd = read(fd, image, size);
	return (image);
}

static void				ft_fill_image(t_texture *img, unsigned char *image,
		t_header *header)
{
	int			x;
	int			y;
	int			i;
	int			z;

	x = 0;
	y = 0;
	z = ((header->y - 1) * (header->x)) * 4;
	i = 0;
	while (i < ((header->x * header->y + 1)))
	{
		if (x > header->x - 1)
		{
			x = 0;
			y++;
			z = ((header->y - (y + 1)) * header->x) * 4;
		}
		pt_to_tex(pt_set(x, y), img, get_color(image[z + (x * 4)],
					image[z + (x * 4) + 1], image[z + (x * 4) + 2],
					image[z + (x * 4) + 3]));
		x++;
		i++;
	}
}

static void				fill_real_size(t_header *header)
{
	t_fill x;
	t_fill y;

	x.val.a = header->image_spec[4];
	x.val.b = header->image_spec[5];
	y.val.a = header->image_spec[6];
	y.val.b = header->image_spec[7];
	header->x = x.value;
	header->y = y.value;
}

int						ft_load_texture(int *endian, char *str, t_texture *img)
{
	int					fd;
	unsigned char		*image;
	t_header			header;

	if ((fd = open(str, O_RDONLY)) == -1)
		return (-1);
	if (ft_fill_header(&header, fd) < 0)
	{
		close(fd);
		return (-1);
	}
	if (header.id_length != 0 && header.color_map_type != 0
			&& header.image_type != 2)
		return (-1);
	fill_real_size(&header);
	image = ft_init_image(fd, &header);
	image = ft_decode_tga(endian, &header, image);
	ft_fill_image(img, image, &header);
	free(image);
	close(fd);
	return (0);
}
