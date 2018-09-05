
# include "parse.h"

void            ft_fill_header(t_header *header, char *buff, int i)
{
	if (i == 0)
		header->id_length = (unsigned char)*buff;
	if (i == 1)
		header->color_map_type = (unsigned char)*buff;
	if (i == 2)
		header->image_type = (unsigned char)*buff;
	if (i < 8 && i > 2)
		header->color_map_spec[i - 3] = (unsigned char)*buff;
	if (i >= 8 && i < 18)
		header->image_spec[i - 8] = (unsigned char)*buff;
}

unsigned char		*ft_init_image(int fd, t_header *header)
{
	unsigned char *image;
	int size;
	int rd;

	image = NULL;
	size = header->x * header->y * 4;
	if (!(image = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		malloc_failed("tga image\n"); //malloc error
; // malloc failled
	rd = read(fd, image, size);
	image[rd] = '\0';
	return (image);
}

unsigned char			*ft_decode_tga(t_header *header, unsigned char *image)
{
	unsigned char 	*end;
	unsigned char	*begin;
	unsigned char	argb[4];

	begin = image;
	end = image + (header->x * header->y * 4);
	/*while (image < end)
	{
		argb[0] = (unsigned char)(*(image + 0));
		argb[1] = (unsigned char)(*(image + 1));
		argb[2] = (unsigned char)(*(image + 2));
		argb[3] = (unsigned char)(*(image + 3));
		image[3] = argb[0];
		image[1] = argb[1];
		image[2] = argb[2];
		image[0] = argb[3];
		image += 4;
	}*/
	while (image < end)
	{
		argb[0] = (unsigned char)(*(image + 0));
		argb[1] = (unsigned char)(*(image + 1));
		argb[2] = (unsigned char)(*(image + 2));
		argb[3] = (unsigned char)(*(image + 3));
		image[3] = argb[0];
		image[2] = argb[1];
		image[1] = argb[2];
		image[0] = argb[3];
		image += 4;
	}
	return (begin);
}

void			ft_fill_image(t_texture *img, unsigned char *image, t_header *header)
{
	int			x;
	int			y;
	int			i;
	int			z;

	y = 0; // * 4;
	i = 0;
	x = 0;
	z = ((header->y -1) * (header->x -1)) * 4;
	while (i < ((header->x * header->y)))
	{
		if (x > header->x -1)
		{
			x = 0;
			y++;
			z = (header->y - y) * header->x * 4;
		}
		pt_to_tex((t_point){x, y}, img, get_color(image[z + (x * 4) + 3], image[z + (x * 4)], image[z + (x * 4) + 1], image[z + (x * 4) + 2]));
		x++;
		i++;
		//i += 4;
	}
}
/*
void			ft_fill_image(t_texture *img, unsigned char *image, t_header *header)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	x = 0;
	while (i < header->x * header->y * 4)
	{
		if (x > header->x - 1)
		{
			x = 0;
			y++;
		}
		pt_to_tex((t_point){x, y}, img, get_color(image[i + 3], image[i], image[i + 1], image[i + 2]));
		x++;
		i += 4;
	}
}*/

void			fill_real_size(t_header *header)
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

void			ft_load_texture(char *str, t_texture *img)
{
	int					fd;
	char				buff[1];
	unsigned char		*image;
	int					rd;
	int					i;
	t_header	 		header;

	if ((fd = open(str, O_RDONLY)) == -1)
		return ;
	i = 0;
	while ((rd = read(fd, buff, 1)) > 0 && i < 20)
		ft_fill_header(&header, buff, i++);
	if (header.id_length != 0 && header.color_map_type != 0 && header.image_type != 2)
		return ;
	fill_real_size(&header);
	image = ft_init_image(fd, &header);
	image = ft_decode_tga(&header, image);
	ft_fill_image(img, image, &header);
	free(image);
	close(fd);
}
