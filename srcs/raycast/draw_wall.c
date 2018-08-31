
#include "main.h"

void        ft_ciel_sol(t_data *data)
{
    int y;

    y = 0;
    while (y < data->ray->wall_min)
    {
        pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, 0x0087CEEB);
        y++;
    }
	y = data->ray->wall_max;
    while (y < WIN_HEIGHT)
    {
        pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, 0x00EED5B7);
        y++;
    }
}

static void				display_wall(t_data *data)
{
	t_point			px_to_color;
	float			coeff;
    
	px_to_color.x = data->ray->actual_ray;
	px_to_color.y = data->ray->wall_min;
	coeff  = (float)data->b_and_w_tiles->size.y / data->ray->wall_size; // scaling texture
    ft_ciel_sol(data);
    while (px_to_color.y < data->ray->wall_max)
    {
        pt_to_tex(px_to_color, data->m_img, get_pixel((t_point){data->ray->offset, (int)(coeff * (float)(px_to_color.y - data->ray->wall_min))}, data->b_and_g_tiles));
        px_to_color.y++;
    }
}

void                fill_coord(t_ptfl *point, t_data *data, float dist_floor)
{
    t_ray *ray;
    t_cam *cam;

    cam = data->cam;
    ray = data->ray;
    if (ray->dist_h < ray->dist_v || ray->dist_v == -1)
    {
        // ray->hori
        //t_ptfl a = set_coeff_x_y_hori(data->ray->deg);
        point->x = cam->crd_real->x
        + (ray->hori.x - cam->crd_real->x)
        * (dist_floor / (ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta)))));

        point->y = cam->crd_real->y
        + (ray->hori.y - cam->crd_real->y)
        * (dist_floor / (ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta)))));
        //*coeff = a.y / 64;
        //if (*coeff < 0)
          //  *coeff = -*coeff;
    }
    else
    {
        // ray->verti
        //t_ptfl a = set_coeff_x_y_verti(data->ray->deg);
        point->x = cam->crd_real->x
        + (ray->verti.x - cam->crd_real->x)
        * (dist_floor / (ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta)))));

        point->y = cam->crd_real->y
        + (ray->verti.y - cam->crd_real->y)
        * (dist_floor / (ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta)))));
        //*coeff = a.x / 64;
        //if (*coeff < 0)
          //  *coeff = -*coeff;
    }
}

void                display_floor(t_data *data)
{
    int ray;

	if (data->ray->wall_min < 0)
		return ;
    float angle_max = rad_to_deg(atan((WIN_HEIGHT * data->cam->h_cam) / (data->ray->dist_w_d))); //* cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta))))));
    float angle_min = rad_to_deg(atan((data->ray->wall_size * data->cam->h_cam) / (data->ray->dist_w_d))); //* cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta))))));
    float delta_angle = angle_max - angle_min;
    float theta_min = delta_angle / data->ray->wall_min;
    t_ptfl point;
    ray = data->ray->wall_max;
    while (ray < WIN_HEIGHT) // changer la taille
    {
        float dist_floor = ((32) / tan(deg_to_rad(angle_max)));
        //printf("%f %f\n", dist_floor, data->ray->dist_w_d);
        if (dist_floor > 0)
        {
            fill_coord(&point, data, dist_floor);
            // print le pixel
            point.x = fmod(point.x * 4, 64);
            point.y = fmod(point.y * 4, 64);
            pt_to_tex((t_point){data->ray->actual_ray, ray}, data->m_img, get_pixel((t_point){point.x, point.y}, data->b_and_g_tiles));
        }
        angle_max += theta_min;
        ray++;
    }
}

void                display_ceiling(t_data *data)
{
    (void)data;
}

void            display_column(t_data *data)
{
    data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
    display_wall(data);
    //display_ceiling(data);
    //display_sky(data);
    display_floor(data);
}
