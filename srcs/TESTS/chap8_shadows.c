/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap8_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:39:16 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/14 17:17:42 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"
//#include "/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include/criterion/criterion.h"
#include "matrix.h"
#include "minirt.h"
#include "extern_libs.h"
#include "tuple.h"
#include "ray.h"
#include "lights.h"
#include "clang_attr.h"
#include "scene.h"

Test(shadows, yes_no)
{
	//ARRANGE
	t_vector	eyev = create_vector(0, 0, 1);
	t_vector	normalv = create_vector(0, 0, -1);
	t_elem	light;
	point_light(&light, create_point(0, 0, -10), create_color(1, 1, 1));
	bool	in_shadow = 1;
	t_elem sphere;
	init_sphere(&sphere);
	sphere.material.color = create_color(1, 1, 1);
	t_rgb	res = lighting(sphere.material, &light, create_point(0, 0, 0), eyev, normalv, in_shadow);
	cr_expect(same_tuple(res, create_color(0.1, 0.1, 0.1)));
}

Test(shadows, no_shadow1)
{
	t_scene	world;
	setup_scene(&world, "./scenes/2spheres1light.rt");
	t_point	p = create_point(0, 10, 0);
	cr_expect(is_shadowed(&world, p) == 0);
	t_point	p2 = create_point(10, -10, 10);
	cr_expect(is_shadowed(&world, p2) == 1);
	t_point	p3 = create_point(-20, 20, -20);
	cr_expect(is_shadowed(&world, p3) == 0);
	t_point	p4 = create_point(-2, 2, -2);
	cr_expect(is_shadowed(&world, p4) == 0);
}

Test(shadows, intersect_shadow)
{
	t_scene	world;
	setup_scene(&world, "./scenes/shadowtest.rt");
	t_ray r = ray(create_point(0, 0, 5), create_vector(0, 0, 1));
	t_inter	i = intersection(4, *world.objs->next);
	prepare_computations(&i, r);
	t_rgb	c  = shade_hit(&world, i);
	cr_expect(same_tuple(c, create_color(0.1, 0.1, 0.1)));
}

Test(shadows, shade_hit_offset)
{
	// t_scene	world;
	// setup_scene(&world, "./scenes/shadowtest.rt");
	t_elem	shape;
	init_sphere(&shape);
	shape.transform = translation(0, 0, 1);
	t_ray r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_inter	i = intersection(5, shape);
	prepare_computations(&i, r);
	cr_expect(i.over_point.z < (-0.00001 / 2));
	cr_expect(i.point.z > i.over_point.z);
	// printf("real x, y, z = %f, %f, %f\n", i.point.z, i.point.y, i.point.z);
	// printf("over x, y, z = %f, %f, %f\n", i.over_point.z, i.over_point.y, i.over_point.z);
}