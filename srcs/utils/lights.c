#include "lights.h"

t_vector	normal_atsphere(t_elem sphere, t_point point)
{
	t_vector	vector;

	vector = normalize(point - sphere.center);
	return (vector);
}
