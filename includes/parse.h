#ifndef PARSE_H
# define PARSE_H

#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/*
** List
*/

void			        ft_add(int x, int y, int content, t_map **map);
t_map			        ***ft_fill_tab(t_parse parse, t_map **map);

/*
** Parse
*/
int						ft_parse(char *str, t_map **map, t_parse *parse);
int				        ft_lin_is_good(char *str);

/*
** Free
*/

void		            free_list(t_map **list);
void		            freetab(t_map ***list);

#endif
