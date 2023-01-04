/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap13_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:16:56 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/04 16:54:57 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mycriterion.h"
#include "minirt.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "lights.h"
#include "scene.h"
#include "inter.h"
#include "setup.h"

float	cylinder_min(t_elem cyl)
{
	t_point	min;

	min = matrix_tuple_mult(cyl.transform, create_point(0, 1, 0));
	return (min.y);
}

float	cylinder_max(t_elem cyl)
{
	t_point	max;

	max = matrix_tuple_mult(cyl.transform, create_point(0, 2, 0));
	return (max.y);
}

t_xs	cylinder_limits(t_elem cyl, t_ray ray, t_xs xs)
{
	(void)cyl;
	float	ymin;
	float	ymax;
	float	y0;
	float	y1;

	ymax = cylinder_max(cyl);
	ymin = cylinder_min(cyl);
	// printf("max = %f, min = %f\n", ymax, ymin);
	y0 = ray.orig.y + xs.t[0] * ray.dir.y;
	if (ymin >= y0 || ymax <= y0)
	{
		// printf("y0 = %f\n", y0);
		xs.count--;
		xs.t[0] = -1;
	}
	y1 = ray.orig.y + xs.t[1] * ray.dir.y;
	if (ymin >= y1 || ymax <= y1)
	{
		// printf("y1 = %f\n", y1);
		xs.count--;
		xs.t[1] = -1;
	}
	return (xs);
}

t_xs	local_intersect_cyl(t_elem cyl, t_ray ray)
{
	(void)cyl;
	float	a;
	float	b;
	float	c;
	float	disc;
	t_xs	xs;

	ray = transform_ray(ray, inverse(cyl.transform));
	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	b = 2 * ray.orig.x * ray.dir.x + 2 * ray.orig.z * ray.dir.z;
	c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1;
	disc = b * b - 4 * a * c;
	if (disc < 0 || (a > -0.001 && a < 0.001))
		ft_bzero(&xs, sizeof(xs));
	else
	{
		xs.count = 2;
		xs.t[0] = (-b - sqrt(disc)) / (2 * a);
		xs.t[1] = (-b + sqrt(disc)) / (2 * a);
		xs = cylinder_limits(cyl, ray, xs);
	}
	return (xs);
}

void	init_cylinder(t_elem *s)
{
	static ssize_t	no = -1;

	no++;
	s->id.shape = cylinder;
	s->id.no = no;
	s->o_pos = create_point(0, 0, 0);
	s->transform = identity_matr();
	s->material = default_material(s);
}

Test(cylinder, ray_misses_cylinder)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	t_ray	r = ray(create_point(1, 0, 0), normalize(create_vector(0, 1, 0)));
	t_xs	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	r = ray(create_point(0, 0, 0), normalize(create_vector(0, 1, 0)));
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	r = ray(create_point(0, 0, -5), normalize(create_vector(1, 1, 1)));
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);
}

// Test(cylinder, ray_hit_cylinder)
// {
// 	t_elem	cyl;
// 	init_cylinder(&cyl);
// 	t_ray	r = ray(create_point(1, 0, -5), normalize(create_vector(0, 0, 1)));
// 	t_xs	xs = local_intersect_cyl(cyl, r);
// 	cr_expect(xs.count == 2);
// 	cr_expect(xs.t[0] == 5);
// 	cr_expect(xs.t[1] == 5);

// 	r = ray(create_point(0, 0, -5), normalize(create_vector(0, 0, 1)));
// 	xs = local_intersect_cyl(cyl, r);
// 	cr_expect(xs.count == 2);
// 	cr_expect(xs.t[0] == 4);
// 	cr_expect(xs.t[1] == 6);

// 	r = ray(create_point(0.5, 0, -5), normalize(create_vector(0.1, 1, 1)));
// 	xs = local_intersect_cyl(cyl, r);
// 	cr_expect(xs.count == 2);
// 	cr_expect(same_float(xs.t[0], 6.80798));
// 	cr_expect(same_float(xs.t[1], 7.08872));
// }

t_vector	local_normal_at_cyl(t_elem cyl, t_point point)
{
	(void)cyl;
	return(create_vector(point.x, 0, point.z));
}

Test(cylinder, cylinder_normal)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	t_vector	n;
	n = local_normal_at_cyl(cyl, create_point(1, 0, 0));
	cr_expect(same_tuple(n, create_vector(1, 0, 0)));

	n = local_normal_at_cyl(cyl, create_point(0, 5, -1));
	cr_expect(same_tuple(n, create_vector(0, 0, -1)));

	n = local_normal_at_cyl(cyl, create_point(0, -2, 1));
	cr_expect(same_tuple(n, create_vector(0, 0, 1)));

	n = local_normal_at_cyl(cyl, create_point(-1, 1, 0));
	cr_expect(same_tuple(n, create_vector(-1, 0, 0)));
}

Test(cylinder, cylinder_infinite)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	cr_expect(cylinder_min(cyl) == 1);
	cr_expect(cylinder_max(cyl) == 2);
}

//cylinder limits dependent of "heigth" in .rt file
//if coordinates are center point, then min is center - height / 2
//and max is center + height / 2
//if heigth and diameter are 1 by default, then scaling(diamet / 2, height, diamet / 2)
//should do the size transformation??



//need to change previous test as this one as same parameters but different expected results...
Test(cylinder, cylinder_finite_ray)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	t_vector dir;
	t_ray r;
	t_xs xs;
	dir = normalize(create_vector(0.1, 1, 0));
	r = ray(create_point(0, 1.5, 0), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	dir = normalize(create_vector(0, 0, 1));
	r = ray(create_point(0, 3, -5), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	dir = normalize(create_vector(0, 0, 1));
	r = ray(create_point(0, 0, -5), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	dir = normalize(create_vector(0, 0, 1));
	r = ray(create_point(0, 2, -5), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	dir = normalize(create_vector(0, 0, 1));
	r = ray(create_point(0, 1, -5), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 0);

	dir = normalize(create_vector(0, 0, 1));
	r = ray(create_point(0, 1.5, -2), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);
}

// Test(cylinder, parse_cylinder)
// {
// 	t_scene	scene;
// 	setup_scene(&scene, ".scene/TESTcylinder.rt");
// 	t_inter	inter;
// 	t_vector dir;
// 	t_ray r;
// 	dir = normalize(create_vector(0.1, 1, 0));
// 	r = ray(create_point(0, 1.5, 0), dir);
// 	inter = intersect_world(&scene, r);
// 	cr_expect(inter.t >= 0);
// }