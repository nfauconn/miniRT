#include "lights.h"

/* find the perpendicular vector to sphere at point */
t_vector	normal_atsphere(t_elem sp, t_point world_pt)
{
	t_point		obj_pt;
	t_vector	obj_normal;
	t_vector	wold_normal;

	obj_pt = matrix_tuple_mult(inverse(sp.transform), world_pt);
	obj_normal = normal_atsphere(sp, sp.obj_space_pos);
	world_normal = matrix_tuple_mult(transpose(inverse(sp.transform)), obj_normal);
	normal = normalize(point - sphere.obj_space_pos);
	return (normal);
}

/*
** to compute the normal on a translated sphere : test(lights, normal_2)
**
*/