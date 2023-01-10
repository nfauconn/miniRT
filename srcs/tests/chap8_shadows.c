/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap8_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:39:16 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/10 19:13:59 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mycriterion.h"
#include "matrix.h"
#include "minirt.h"
#include "tuple.h"
#include "ray.h"
#include "lights.h"
#include "scene.h"
#include "inter.h"
#include "setup.h"

Test(shadows, yes_no)
{
	t_scene		scene;
	setup_scene(&scene, "./scenes/TEST2spheres1light.rt");

	t_inter		inter;
	//ARRANGE
	inter.eyev = create_vector(0, 0, 1);
	inter.normalv = create_vector(0, 0, -1);
	inter.over_point = create_point(0, 0, 0);

	t_elem	light;
	point_light(&light, create_point(0, 0, -10), create_color(1, 1, 1));

	bool	shadowed = 1;

	t_elem sphere;
	init_sphere(&sphere);
	sphere.material.color = create_color(1, 1, 1);

	inter.obj = &sphere;
	t_rgb	res = lighting(&scene, &light, inter, shadowed);
	cr_expect(same_tuple(res, create_color(0.1, 0.1, 0.1)));
}

Test(shadows, no_shadow1)
{
	t_scene	world;
	setup_scene(&world, "./scenes/TEST2spheres1light.rt");
	t_point	p = create_point(0, 10, 0);
	cr_expect(is_shadowed(&world, world.lights, p) == 0);
	t_point	p2 = create_point(10, -10, 10);
	cr_expect(is_shadowed(&world, world.lights, p2) == 1);
	t_point	p3 = create_point(-20, 20, -20);
	cr_expect(is_shadowed(&world, world.lights, p3) == 0);
	t_point	p4 = create_point(-2, 2, -2);
	cr_expect(is_shadowed(&world, world.lights, p4) == 0);
}

Test(shadows, intersect_shadow)
{
	t_scene	world;
	setup_scene(&world, "./scenes/TESTshadow.rt");
	t_ray r = ray(create_point(0, 0, 5), create_vector(0, 0, 1));
	t_inter	i = intersection(4, world.objs->next);
	prepare_computations(&i, r);
	t_rgb	c  = shade_hit(&world, i);
	cr_expect(same_tuple(c, create_color(0.1, 0.1, 0.1)));
}

Test(shadows, shade_hit_offset)
{
	// t_scene	world;
	// setup_scene(&world, "./scenes/TESTshadow.rt");
	t_elem	shape;
	init_sphere(&shape);
	shape.transform = translation(0, 0, 1);
	t_ray r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_inter	i = intersection(5, &shape);
	prepare_computations(&i, r);
	cr_expect(i.over_point.z < (-0.00001 / 2));
	cr_expect(i.point.z > i.over_point.z);
	// printf("real x, y, z = %f, %f, %f\n", i.point.z, i.point.y, i.point.z);
	// printf("over x, y, z = %f, %f, %f\n", i.over_point.z, i.over_point.y, i.over_point.z);
}