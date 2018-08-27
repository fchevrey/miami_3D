#include "main.h"

void		set_real_to_map(t_point *real, t_point *map)
{
	map->x = real->x / SIZE_GRID;
	map->y = real->y / SIZE_GRID;
}

void		set_map_to_real(t_point *map, t_point *real)
{
	real->x = map->x * SIZE_GRID;
	real->y = map->y * SIZE_GRID;
}

t_point		get_map_from_real(t_point *real)
{
	t_point		map;

	map.x = real->x / SIZE_GRID;
	map.y = real->y / SIZE_GRID;
	return (map);
}

t_point		get_real_from_map(t_point *map)
{
	t_point		real;

	real.x = map->x * SIZE_GRID;
	real.y = map->y * SIZE_GRID;
	return (real);
}
