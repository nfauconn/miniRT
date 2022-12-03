#include "lights.h"

/* find the perpendicular vector to sphere at point */
t_vector	normal_atsphere(t_elem *sp, t_point world_pt)
{
	t_point		o_pt;
	t_vector	o_normal;
	t_vector	w_normal;

	o_pt = matrix_tuple_mult(inverse(sp->transform), world_pt);
	o_normal = o_pt - sp->o_pos;
	w_normal = matrix_tuple_mult(transpose(inverse(sp->transform)), o_normal);
	w_normal.w = 0;
	return (normalize(w_normal));
}

/*
** to compute the normal on a translated sphere : test(lights, normal_2)
**
*/