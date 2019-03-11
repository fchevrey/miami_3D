#ifndef MAIN_H
# define MAIN_H

#include <math.h>

#include "mymath.h"
#include "libft.h"
#include "libmysdl.h"
#include "libpt.h"
#include "struct.h"
#include "defines.h"
#include "raycast.h"
#include "parse.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdio.h>

void			malloc_failed(char *str);
void			ft_exit(t_data **data);
t_data			*data_init(t_map ***map, t_parse parse, char **av);
void			display_map(t_map ***map2, int x, int y, t_data *data);//
int			 	is_in_map(float x, float y, t_data *data);
int				ft_error(const char *str1, const char *str2,
		const char *str3);
int				sound_init(t_data *data);

/*
** Tool to pass from real scale from map scale
*/
void			set_real_to_map(t_point *real, t_point *map);
void			set_map_to_real(t_point *map, t_point *real);
t_point			get_map_from_real(t_point *real);
t_point			get_real_from_map(t_point *map);

/*
** mini_map
*/

void			mini_map(t_data *data);
void			draw_mini_map2(t_data *data);

#endif
