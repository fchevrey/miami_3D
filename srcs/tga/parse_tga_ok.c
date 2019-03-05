
# include "parse.h"

void            ft_fill_header(t_header *header, char *buff, int i)
{
	if (i == 0)
		header->id_length = (unsigned char)*buff;
	if (i == 1)
		header->color_map_type = (unsigned char)*buff;
	if (i == 2)
		header->image_type = (unsigned char)*buff;
	if (i > 2 && i < 8)
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
	if (!(image = (unsigned char *)malloc(sizeof(unsigned char) * size + 1)))
		malloc_failed("tga image\n"); //malloc error
; // malloc failed
	rd = read(fd, image, size);
	image[rd] = '\0';
	return (image);
}

void			ft_fill_image(t_texture *img, unsigned char *image, t_header *header)
{
	int			x;
	int			y;
	int			i;
	int			z;

	x = 0;
	y = 0; // * 4;
	z = ((header->y -1) * (header->x)) * 4;
	//z = ((header->y) * (header->x)) * 4;
	printf("z = %d y = %d\n", z, y);
	i = 0;
	while (i < ((header->x * header->y)))
	{
		if (x > header->x -1)
		{
			x = 0;
			y++;
			z = ((header->y - (y + 1)) * (header->x)) * 4;
		}
		pt_to_tex((t_point){x, y}, img, get_color(image[z + (x * 4)], image[z + (x * 4) + 1], image[z + (x * 4) + 2], image[z + (x * 4) + 3]));
		if (get_pixel(pt_set(x, y), img) == (uint32_t)4278190080)
		{
			printf("i = %d  (%d, %d) => color = %08x\n", i, x, y, get_pixel(pt_set(x, y), img));
			printf("get_color = %08x\n", get_color(image[z + (x * 4) ], image[z + (x * 4) +1], image[z + (x * 4) + 2], image[z + (x * 4) + 3]));
		}
		if(i < 5 || i == 63)
			printf("i = %d, get_color = %08x\n", i, get_color(image[z + (x * 4)], image[z + (x * 4) + 1], image[z + (x * 4)+2], image[z + (x * 4) + 3]));
		x++;
		i++;
		//i += 4;
	}
	//printf("i = %d\n", i -1);
	//printf("0,0 = 0x%08x\n, 63,63 = %u   lenght = %d, %d\n", get_pixel(pt_set(0, 0), img), get_pixel(pt_set(63,63), img), img->size.x, img->size.y);
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
	printf("largeur image en pixel = %d, hauteur image en pixels = %d\n",header->x, header->y);
}
void			print_header(t_header *header)
{//
	printf("HEADER\n");
	printf("---\nid_lenght = %u\n", header->id_length);
	printf("colormap = %u\n", header->color_map_type);
	printf("image type = %u\n", header->image_type);
	printf("x = %hd\n", header->x);
	printf("y = %hd\n---\n", header->y);
}

void			ft_load_texture(int *endian, char *str, t_texture *img)
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
	while (i < 18 && (rd = read(fd, buff, 1)) > 0)
		ft_fill_header(&header, buff, i++);
	if (header.id_length != 0 && header.color_map_type != 0 && header.image_type != 2)
		return ;
	fill_real_size(&header);
	image = ft_init_image(fd, &header);
	image = ft_decode_tga(endian, &header, image);
	ft_fill_image(img, image, &header);
	print_header(&header);
	free(image);
	close(fd);
}
