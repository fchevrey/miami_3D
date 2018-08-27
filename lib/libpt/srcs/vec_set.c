#include "libpt.h"

t_vec	vec_set(int x, int y, int z)
{
	t_vec	crd;

	crd.x = x;
	crd.y = y;
	crd.z = z;
	return (crd);
}
