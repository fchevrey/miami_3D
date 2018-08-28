
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

float				distance_wall_sky(t_point b, t_point a)
{
	return (sqrt(pow((b.x - a.x),2) + pow((b.y - a.y), 2)));
}

t_point			return_point_skybox(t_data *data, float *distance)
{
	float deg;
	t_point	point;
	t_point p;

	p.x = (data->ray->dist_h > data->ray->dist_v) ? data->ray->verti.x : data->ray->hori.x;
	p.y = (data->ray->dist_h > data->ray->dist_v) ? data->ray->verti.y : data->ray->hori.y;
	deg = data->ray->deg;
	if (deg > 45 && deg < 135) // up
	{
		point.x = p.x;
		point.y = - SKYBOX / 64;	
	}
	else if (deg > 135 && deg < 225) // left
	{
		point.x = - SKYBOX / 64;
		point.y = p.y;
	}
	else if (deg > 225 && deg < 315) // right
	{
		point.x = data->xmax + SKYBOX / 64;
		point.y = p.y;
	}
	else // down
	{
		point.x = p.x;
		point.y = data->ymax + SKYBOX / 64;
	}
	*distance = distance_wall_sky(point, p);
	return (point);
}

void                display_sky(t_data *data)
{
    int ray;

    float angle_max = rad_to_deg(atan((WIN_HEIGHT * data->cam->h_cam) / data->ray->dist_w_d));
    float angle_min = rad_to_deg(atan((data->ray->wall_size * data->cam->h_cam) / data->ray->dist_w_d));
    float delta_angle = angle_max - angle_min;
	float distance;
    float theta_min = delta_angle / data->ray->wall_min;
    ray = 0;
    while (ray < data->ray->wall_min)
    {
        // float distance = data->ray->dist_w_d * cos(deg_to_rad(angle_max));
        // trouver le point de la Skybox et la distance
		t_point sky = return_point_skybox(data, &distance);
		(void)sky;
		// trouver angle absolu du rayon
        // rectifier la distance  (multiplie par cos angle)
        // trouver le deuxieme point rectifié
        // C'est ce point ou on va mettre texture
        angle_max -= theta_min;
        ray++;
    }
}