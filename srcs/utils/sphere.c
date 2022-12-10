#include "minirt.h"

t_material	default_material(t_elem *elem)
{
	t_material	material;

	material.color = elem->color;
	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;
	return (material);
}

void	init_sphere(t_elem *s)
{
	static ssize_t	no = -1;

	no++;
	s->id.shape = sphere;
	s->id.no = no;
	s->o_pos = create_point(0, 0, 0);
	s->transform = identity_matr();
	s->material = default_material(s);
}
