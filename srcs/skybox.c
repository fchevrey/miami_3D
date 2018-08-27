
# include "main.h"

typedef struct		s_sky
{
	t_texture		*ciel;
	t_texture		*sol;
	t_texture		*nord;
	t_texture		*sud;
	t_texture		*est;
	t_texture		*ouest;
	t_point			size;
	int				hauteur;
}					t_sky;

void			ft_init_sky(t_sky *sky, t_data *data)
{
	t_point size;

	size.x = 256;
	size.y = 256;
	sky->hauteur = 640;
	sky->size.x = data->xmax * 3;
	sky->size.y = data->ymax * 3;
	if (!(sky->ciel = texture_new(size, data->win->ren)))
		malloc_failed("init sky\n"); //malloc error
	if (!(sky->sol = texture_new(size, data->win->ren)))
		malloc_failed("init sky\n"); //malloc error
	if (!(sky->nord = texture_new(size, data->win->ren)))
		malloc_failed("init sky\n"); //malloc error
	if (!(sky->sud = texture_new(size, data->win->ren)))
		malloc_failed("init sky\n"); //malloc error
	if (!(sky->est = texture_new(size, data->win->ren)))
		malloc_failed("init sky\n"); //malloc error
	if (!(sky->ouest = texture_new(size, data->win->ren)))
		malloc_failed("init sky\n"); //malloc error
	ft_load_texture("assets/textures/skybox/haut.tga", sky->ciel);
	ft_load_texture("assets/textures/skybox/bas.tga", sky->sol);
	ft_load_texture("assets/textures/skybox/nord.tga", sky->nord);
	ft_load_texture("assets/textures/skybox/sud.tga", sky->sud);
	ft_load_texture("assets/textures/skybox/est.tga", sky->est);
	ft_load_texture("assets/textures/skybox/ouest.tga", sky->ouest);
}

