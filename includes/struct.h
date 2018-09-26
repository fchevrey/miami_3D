#ifndef STRUCT_H
# define STRUCT_H
# include <stdint.h>
# include "main.h"
# include "defines.h"
#include "SDL_mixer.h"

typedef struct			s_obj
{
	t_ptfl				obj_pt;
	t_point				obj_pt_map;
	int					content;
	int					index;
	int					x;
	int					obj_dist;
	int					wall_dist;
	int					obj_height;
	int					obj_depth;
//	struct s_obj		*next;
//	struct s_obj		*prev;
}						t_obj;

typedef struct 			s_ray
{
	float				deg;
	int					actual_ray;
	t_ptfl				coeff;
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
	t_point				*crd_map;	// coordonnee sur le tableau
	t_point				*crd_real;	// coordonnee sur la grille
	t_point				act_inter; // point d'intersection entre le dernier rayon et le mur (utile pour le RayCasting des textures des murs)
	float				theta;   	// position de la cam en degree par rapport a l'axe x
	float				len_cam; 	// Distance camera / ecran
	float				h_cam;   	// Hauteur camera
	float				min_theta;  // angle entre chaque rayons
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
	Mix_Music			**musics;
	t_map				***map;
	t_texture			*m_img;
	t_texture			*hud;
	t_texture			**floor_texts;
	t_texture			**wall_texts;
	t_texture			**obj_texts;
	t_cam				*cam;
	t_ray				*ray;
	t_obj				obj_ar[OBJ_NB];
	int					endian; //little = 0 and big = 1
	uint8_t				walking;
}						t_data;

typedef struct			s_funar_keyb
{
	int					key;
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
