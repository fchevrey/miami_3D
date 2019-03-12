#ifndef STRUCT_H
# define STRUCT_H
# include <stdint.h>
# include "main.h"
# include "SDL_mixer.h"

typedef struct			s_obj
{
	t_ptfl				obj;
	int					content;
	struct s_obj		*next;
	struct s_obj		*prev;
}						t_obj;

typedef struct			s_ray
{
	float				deg;
	int					actual_ray;
	t_ptfl				hori;
	t_ptfl				verti;
	float				dist_h;
	float				dist_v;
	float				dist_w_d;
	int					offset;
	float				wall_size;
	int					wall_min;
	int					wall_max;
}						t_ray;

typedef union			u_color
{
	uint32_t			c;
	struct				s_argb
	{
		uint8_t			b;
		uint8_t			g;
		uint8_t			r;
		uint8_t			a;
	}					argb;
}						t_color;

/*
** Structure contenant diverses infos venant du parsing
*/

typedef struct			s_parse
{
	int					nb_elem_line;
	int					nb_line;
}						t_parse;

/*
** Structure qui va devenir une liste chainee
** puis un double tableau de pointeur sur structure
*/

typedef struct			s_map
{
	int					x;
	int					y;
	int					content;
	struct s_map		*next;
	struct s_map		*prev;
}						t_map;

/*
** POV du joueur
*/

typedef struct			s_cam
{
	t_point				*crd_map;
	t_point				*crd_real;
	t_point				act_inter;
	float				theta;
	float				len_cam;
	float				h_cam;
	float				min_theta;
}						t_cam;

/*
** Structure principale
*/

typedef struct			s_data
{
	t_win				*win;
	char				*path;
	int					xmax;
	int					ymax;
	Mix_Chunk			**sounds;
	int					walk_channel;
	int					len_music;
	Mix_Music			**musics;
	t_map				***map;
	t_texture			*m_img;
	t_texture			*hud;
	t_texture			**wall_texts;
	t_texture			**texts;
	t_cam				*cam;
	t_ray				*ray;
	int					endian;
	uint8_t				walking;
}						t_data;

typedef struct			s_funar_keyb
{
	int					key;
	int					repeat;
	void				(*f)(t_data*);
}						t_funar_keyb;

/*
** Structure t_point mais avec des floats pour plus de precision
*/

typedef	struct			s_fpoint
{
	float				x;
	float				y;
}						t_fpoint;

#endif
