#include "raycast.h"

int				set_offset(t_point hori, t_point verti, float dist_h, float dist_v)
{
	int			offset;;

	offset = 0;
	if (dist_v < 0 || dist_h < dist_v)
	{
		offset = hori.x;
//		printf("\nIntersection HORI :");
	}
	else if (dist_h < 0 || dist_h > dist_v)
	{
		offset = verti.y;
//		printf("Intersection VERTI :");
	}
//	printf(" valeur initiale offset.x = %d\n", offset.x);
	offset = offset % 64;
//		printf("valeur apres modulo 64 : offset.x = %d\n\n", offset.x);
	return (offset);
}
