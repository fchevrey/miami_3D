#ifndef STRUCT_H
# define STRUCT_H
# include <stdint.h>
# include "main.h"
# include "defines.h"
#include "SDL_mixer.h"


/*
** Contient toutes les donnees relatives a un objet pour une seule colonne
** de l'ecran (hauteur, profondeur)
*/
typedef struct			s_coord
{
	int					ray_nb;
	t_ptfl				obj_pt;
	t_point				obj_pt_map;
	int					x;
	float				obj_dist;
	float				wall_dist;
	float				obj_height;
	float				obj_depth;
}						t_coord;


/*
** Contient toutes les donnees relatives a un objet pour toute sa largeur
*/
typedef struct			s_obj
{
	int					content;
	int					index;
	int					x;
	t_coord				coord[WIN_WIDTH];
	float				width;
//	struct s_obj		*next;
//	struct s_obj		*prev;
}						t_obj;

typedef struct 			s_ray
{
	float				deg;
	int					act_ray;
	t_ptfl				coeff_h;
	t_ptfl				coeff_v;
	t_ptfl				hori;
	t_ptfl				verti;
	float				dist_h;
	float				dist_v;
	float				dist_w_d;
	float				wall_dist;
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
	t_cam				*cam;
	t_ray				*ray_ar[WIN_WIDTH];
	t_obj				obj_ar[OBJ_NB];
	Mix_Chunk			**sounds;
	Mix_Music			**musics;
	t_map				***map;
	t_texture			*m_img;
	t_texture			*hud;
	t_texture			**floor_texts;
	t_texture			**wall_texts;
	t_texture			**obj_texts;
	t_point				last_obj;
	char				*path;
	int					xmax;
	int					ymax;
	int					endian; //little = 0 and big = 1
	int					walk_channel;
	int					act_ray;// index du ray en cours
	uint8_t				walking;
}						t_data;

typedef struct			s_funar_keyb
{
	int					key;
	void				(*f)(t_data*);
}						t_funar_keyb;

#endif
