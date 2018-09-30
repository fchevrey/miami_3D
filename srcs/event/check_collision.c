#include "event.h"

static int		check_map(t_point crd, t_data *data)
{
	t_point		crd_map;

	crd_map = get_map_from_real(&crd);
	//printf("crd map = (%d, %d) ", crd_map.x, crd_map.y);
	if (is_in_map(crd_map.x, crd_map.y, data))
		return (data->map[crd_map.y][crd_map.x]->content);
	return (-1);
}

static t_point		huge_gradient(t_point pt1, t_point pt2, float gradient,
		t_data *data)
{
	t_point		crd;
	int			ret;
	int			incr;

//	printf("Huge pt1x = %d y = %d pt2 x= %d y= %d\n", pt1.x, pt1.y, pt2.x, pt2.y);
	incr = 1;
	if (pt1.y > pt2.y)
		incr = -1;
	crd = pt_set(pt1.x, pt1.y);
	while (crd.y != pt2.y)
	{
		crd.x = pt1.x + (int)((crd.y - pt1.y) / gradient);
		if ((ret = check_map(crd, data)) > 0)
		{
			//printf("wall at x = %d, y = %d\n", crd.x, crd.y);
			crd.x = pt1.x - (int)((crd.y - pt1.y) / gradient);
			crd.y -= incr;
			return (crd);
		}
		else if (ret == -1)
		{
			//printf("! exit map !crd.x = %d y = %d  content = %d\n", crd.x, crd.y, ret);
			crd.y -= incr;
			crd.x = pt1.x - (int)((crd.y - pt1.y) / gradient);
			return (crd);
		}
	//	printf("ret = %d, ", ret);
		crd.y += incr;
	}
	//printf("\nend while : crd.x = %d y = %d \n", crd.x, crd.y);
	return (crd);
}

static t_point		low_gradient(t_point pt1, t_point pt2, float gradient,
	t_data *data)
{
	t_point		crd;
	int			ret;
	int			incr;

	incr = 1;
	if (pt1.x > pt2.x)
		incr = -1;
	crd = pt_set(pt1.x, pt1.y);
		if (check_map(crd, data) > 0)
			return (crd);
	while (crd.x != pt2.x)
	{
		crd.y = pt1.y + (int)(gradient * (crd.x - pt1.x));
		if ((ret = check_map(crd, data)) > 0)
		{
			//printf("low_grad wall at x = %d, y = %d\n", crd.x, crd.y);
			crd.y = pt1.y - (int)(gradient * (crd.x - pt1.x));
			crd.x -= incr;
			return (crd);
		}
		//printf("ret = %d, ", ret);
		crd.x += incr;
	}
//	printf("Low end while\n");
	return (crd);
}

t_point			check_collision(t_point old, t_point new, t_data *data)
{
	float		gradient;
	int			divideur;

	divideur = (int)abs(new.x - old.x);
	if (divideur == 0)
		divideur = 1;
	gradient = (float)(old.y - new.y) / divideur;
	if (gradient > -1.5 && gradient < 1.5)
		return (low_gradient(old, new, gradient, data));
	else
		return (huge_gradient(old, new, gradient, data));
}
