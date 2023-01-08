/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap13_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:16:56 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/07 15:47:14 by rokerjea         ###   ########.fr       */
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

	min = matrix_tuple_mult(cyl.transform, create_point(0, -0.5, 0));
	// printf("min. x,y,z = %f, %f, %f\n", min.x, min.y, min.z);
	return (min.y);
}

float	cylinder_max(t_elem cyl)
{
	t_point	max;

	max = matrix_tuple_mult(cyl.transform, create_point(0, 0.5, 0));
	return (max.y);
}

t_xs	cylinder_limits(t_elem cyl, t_ray ray, t_xs xs)
{
	float	ymin;
	float	ymax;
	float	y0;
	float	y1;

	ymax = cylinder_max(cyl);
	ymin = cylinder_min(cyl);
	// printf("max = %f, min = %f\n", ymax, ymin);
	y0 = ray.orig.y + (xs.t[0] * ray.dir.y);
	if (y0 <= ymin || y0 >= ymax)
	{
		// printf("y0 = %f\n", y0);
		xs.count--;
		xs.t[0] = -1;
	}
	y1 = ray.orig.y + (xs.t[1] * ray.dir.y);
	if (y1 <= ymin || y1 >= ymax)
	{
		// printf("y1 = %f\n", y1);
		xs.count--;
		xs.t[1] = -1;
	}
	return (xs);
}

int	check_cap(t_ray r, int t)
{
	int	x;
	int	z;

	x = r.orig.x + (t * r.dir.x);
	z = r.orig.z + (t * r.dir.z);
	return((x * x + z * z) <= 1);
}

t_xs	add_t_to_xs(t_xs xs, int t)
{
	if (xs.count == 0)
	{
		xs.t[0] = t;
		xs.count++;
	}
	else if (xs.count == 1)
	{
		xs.t[1] = t;
		xs.count++;
	}
	return (xs);
}

t_xs	intersect_cyl_caps(t_elem cyl, t_ray r, t_xs xs)
{
	int	t;

	if (r.dir.y < EPSILON && r.dir.y > -EPSILON)
		return (xs);
	t = (cylinder_min(cyl) - r.orig.y) / r.dir.y;
	if (check_cap(r, t))
		xs = add_t_to_xs(xs, t);
	t = (cylinder_max(cyl) - r.orig.y) / r.dir.y;
	if (check_cap(r, t))
		xs = add_t_to_xs(xs, t);
	return (xs);
}

// t_xs	local_intersect_cyl(t_elem cyl, t_ray ray)
// {
// 	(void)cyl;
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	disc;
// 	t_xs	xs;

// 	ray = transform_ray(ray, inverse(cyl.transform));
// 	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
// 	b = 2 * ray.orig.x * ray.dir.x + 2 * ray.orig.z * ray.dir.z;
// 	c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1;
// 	disc = b * b - 4 * a * c;
// 	if (disc < 0 || (a > -0.001 && a < 0.001))
// 		ft_bzero(&xs, sizeof(xs));
// 	else
// 	{
// 		xs.count = 2;
// 		xs.t[0] = (-b - sqrt(disc)) / (2 * a);
// 		xs.t[1] = (-b + sqrt(disc)) / (2 * a);
// 		xs = cylinder_limits(cyl, ray, xs);
// 	}
// 	if (xs.count < 2)
// 		xs = intersect_cyl_caps(cyl, ray, xs);
// 	return (xs);
// }

t_xs	local_intersect_cyl(t_elem cyl, t_ray ray)
{
	t_xs	xs;
	float	a;
	float	b;
	float	c;
	float	disc;

	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	b = (2 * ray.orig.x * ray.dir.x) + (2 * ray.orig.z * ray.dir.z);
	c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1;
	disc = (b * b) - (4 * a * c);
	if (disc < 0 || (a > -0.001 && a < 0.001))
		ft_bzero(&xs, sizeof(xs));
	else
	{
		xs.count = 2;
		xs.t[0] = (-b -sqrt(disc)) / (2 * a);
		xs.t[1] = (-b +sqrt(disc)) / (2 * a);
		if (xs.t[0] > xs.t[1])
		{
			c = xs.t[0];
			xs.t[0] = xs.t[1];
			xs.t[1] = c;
		}
		xs = cylinder_limits(cyl, ray, xs);
	}
	if	(xs.count < 2 && cyl.specs.fov == 1)
		xs = intersect_cyl_caps(cyl, ray, xs);
	return (xs);
}

void	init_cylinder(t_elem *s)
{
	static ssize_t	no = -1;

	no++;
	s->id.shape = cylinder;
	s->id.no = no;
	s->specs.fov = 0;
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

Test(cylinder, ray_hit_cylinder)
{
	t_elem	cyl;
	init_cylinder(&cyl);

	cyl.specs.diam_hght[1] = 20000;
	cyl.transform = scaling (1, cyl.specs.diam_hght[1], 1);

	t_ray	r = ray(create_point(1, 0, -5), normalize(create_vector(0, 0, 1)));
	t_xs	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);
	cr_expect(xs.t[0] == 5);
	cr_expect(xs.t[1] == 5);

	r = ray(create_point(0, 0, -5), normalize(create_vector(0, 0, 1)));
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);
	cr_expect(xs.t[0] == 4);
	cr_expect(xs.t[1] == 6);

	r = ray(create_point(0.5, 0, -5), normalize(create_vector(0.1, 1, 1)));
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);
	cr_expect(same_float(xs.t[0], 6.80798));
	cr_expect(same_float(xs.t[1], 7.08872));
}

t_vector	local_normal_at_cyl(t_elem cyl, t_point point)
{
	t_point		local_pt;
	t_vector	local_normal;
	t_vector	w_normal;
	float		dist;

	// local_pt = matrix_tuple_mult(inverse(cyl.transform), point);
	local_pt = point;
	dist = (local_pt.x * local_pt.x) + (local_pt.z * local_pt.z);
	// printf("local_pt.y = %f, cyl max = %f\n", local_pt.y, cylinder_max(cyl));
	if (dist < 1 && local_pt.y >= (cylinder_max(cyl) - EPSILON))
	{
		local_normal = create_vector(0, 1, 0);
	}
	else if (dist < 1 && local_pt.y <= (cylinder_min(cyl) + EPSILON))
		local_normal = create_vector(0, -1, 0);
	else
		local_normal = create_vector(local_pt.x, 0, local_pt.z);
	w_normal = matrix_tuple_mult(inverse(transpose(cyl.transform)), local_normal);
	w_normal.w = 0;
	return (normalize(w_normal));
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
	cyl.specs.diam_hght[1] = 20000;
	cyl.transform = scaling (1, cyl.specs.diam_hght[1], 1);
	cr_expect(cylinder_min(cyl) == -10000);
	cr_expect(cylinder_max(cyl) == 10000);
}

//cylinder limits dependent of "heigth" in .rt file
//if coordinates are center point, then min is center - height / 2
//and max is center + height / 2
//if heigth and diameter are 1 by default, then scaling(diamet / 2, height, diamet / 2)
//should do the size transformation??

Test(cylinder, cylinder_finite_ray)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	cyl.transform = translation(0, 1.5, 0);
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


Test(cylinder, cylinder_capped)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	cyl.transform = translation(0, 1.5, 0);
	cyl.specs.fov = 1;
	t_vector dir;
	t_ray r;
	t_xs xs;
	dir = normalize(create_vector(0, -1, 0));
	r = ray(create_point(0, 3, 0), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);

	dir = normalize(create_vector(0, -1, 2));
	r = ray(create_point(0, 3, -2), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);//test with ray that cross a side and a cap

	dir = normalize(create_vector(0, -1, 1));
	r = ray(create_point(0, 4, -2), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);//test cap and corner of cap

	dir = normalize(create_vector(0, 1, 2));
	r = ray(create_point(0, 0, -2), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);//test with ray that cross a side and a cap

	dir = normalize(create_vector(0, 1, 1));
	r = ray(create_point(0, -1, -2), dir);
	xs = local_intersect_cyl(cyl, r);
	cr_expect(xs.count == 2);//test cap and corner of cap
}

Test(cylinder, normal_of_caps)
{
	t_elem	cyl;
	init_cylinder(&cyl);
	cyl.transform = translation(0, 1.5, 0);
	cyl.specs.fov = 1;
	t_point point;
	t_vector	vec;

	point = create_point(0, 1, 0);
	vec = local_normal_at_cyl(cyl, point);
	cr_expect(same_tuple(vec, create_vector(0, -1, 0)));
	point = create_point(0.5, 1, 0);
	vec = local_normal_at_cyl(cyl, point);
	cr_expect(same_tuple(vec, create_vector(0, -1, 0)));
	point = create_point(0, 1, 0.5);
	vec = local_normal_at_cyl(cyl, point);
	cr_expect(same_tuple(vec, create_vector(0, -1, 0)));
	point = create_point(0, 2, 0);
	vec = local_normal_at_cyl(cyl, point);
	cr_expect(same_tuple(vec, create_vector(0, 1, 0)));
	// printf("vex x y z = %f, %f, %f\n", vec.x, vec.y, vec.z);
	point = create_point(0.5, 2, 0);
	vec = local_normal_at_cyl(cyl, point);
	cr_expect(same_tuple(vec, create_vector(0, 1, 0)));
	// printf("vex x y z = %f, %f, %f\n", vec.x, vec.y, vec.z);
	point = create_point(0, 2, 0.5);
	vec = local_normal_at_cyl(cyl, point);
	cr_expect(same_tuple(vec, create_vector(0, 1, 0)));
	// printf("vex x y z = %f, %f, %f\n", vec.x, vec.y, vec.z);
}
