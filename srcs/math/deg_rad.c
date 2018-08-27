#include "mymath.h"

float		deg_to_rad(float deg)
{
	return ((deg * M_PI) / 180);
}

float		rad_to_deg(float rad)
{
	return ((rad * 180) / M_PI);
}
