#ifndef STRUCT_H
# define STRUCT_H
# include <stdint.h>
# include "main.h"
#include "SDL_mixer.h"

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
	t_win		*win;
	char		*path;
	int			xmax;
	int			ymax;
	Mix_Chunk	**sounds;
	int			walk_channel;
	Mix_Music	**musics;
	t_map		***map;
	t_texture	*m_img;
	t_texture	*b_and_w_tiles;
	t_cam		*cam;
	uint8_t		walking;
}						t_data;

typedef struct			s_funar_keyb
{
	int					key;
	void				(*f)(t_data*);
}						t_funar_keyb;

#endif
