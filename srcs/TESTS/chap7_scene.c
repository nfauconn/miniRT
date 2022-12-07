/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap7_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:29:05 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/07 18:34:21 by nfauconn         ###   ########.fr       */
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

Test(scene, world)
{
	t_scene	world;
	setup_scene(&world, "./scenes/empty.rt");
	cr_expect(world.objs == NULL);
	cr_expect(world.lights == NULL);
	clear (&world);
}

void	print_tuple(t_float4 var)
{
	printf("%f, %f, %f, %f \n", var.x, var.y, var.z, var.w);
}

Test(scene, default)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	cr_expect(same_tuple(world.lights->color, (t_float4){255, 255, 255, 0}));
	cr_expect(same_tuple(world.lights->w_pos, (t_float4){-10, 10, -10, 1}));
	// print_tuple(world.lights->w_pos);
	t_elem	*sp = world.objs;
	t_float4	color = create_color(204, 255, 153);
	cr_expect(same_tuple(sp->color, color));
	sp = sp->next;
	t_m4x4_f	transform = scaling(0.5, 0.5, 0.5);
	set_transform(sp, transform);
	cr_expect(same_matrix(sp->transform, transform));
	// printf_4fmatr(transform);
	// printf_4fmatr(sp.transform);
	clear (&world);
}

void	print_shape(t_elem *shape)
{
	printf("center = ");
	print_tuple(shape->w_pos);
	printf("pos = ");
	print_tuple(shape->o_pos);
	printf("color = ");
	print_tuple(shape->color);
	printf("specs = %f\n", shape->specs.radius);
}

Test(scene, world_ray)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	world.objs->transform = identity_matr();
	// print_shape(world.objs);
	t_ray r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_xs	intelist = intersect(*world.objs, r);
	cr_expect(same_float(intelist.t[0], 4.0));
	printf("%f\n", intelist.t[0]);
	printf("%f\n", intelist.t[1]);
	clear (&world);
}

Test(scene, precompute)
{
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_elem	shape;
	init_sphere(&shape);
	t_inter	i = intersection(4, shape);

	t_comps	comps = prepare_computations(i, r);

	cr_expect(same_float(comps.t, i.t) == 1);
	// cr_expect(&comps.obj == &i.obj);
	cr_expect(same_tuple(comps.point , create_point(0, 0, -1)));
	cr_expect(same_tuple(comps.eyev , create_vector(0, 0, -1)));
	cr_expect(same_tuple(comps.normalv , create_vector(0, 0, -1)));
}

Test(scene, outside)
{
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_elem	shape;
	init_sphere(&shape);
	t_inter	i = intersection(4, shape);

	t_comps	comps = prepare_computations(i, r);

	cr_expect(!comps.inside);
}

Test(scene, inside)
{
	t_ray	r = ray(create_point(0, 0, 0), create_vector(0, 0, 1));
	t_elem	shape;
	init_sphere(&shape);
	t_inter	i = intersection(1, shape);

	t_comps	comps = prepare_computations(i, r);

	cr_expect(same_tuple(comps.point , create_point(0, 0, 1)));
	cr_expect(same_tuple(comps.eyev , create_vector(0, 0, -1)));
	cr_expect(comps.inside);
	cr_expect(same_tuple(comps.normalv , create_vector(0, 0, -1)));
}

Test(scene, shade_out)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_elem	*shape = world.objs;
	t_inter	i = intersection(4, *shape);
	t_comps	comps = prepare_computations(i, r);

	t_rgb	c = shade_hit(&world, comps);

	cr_expect(same_tuple(c, create_vector(0.38066, 0.47583, 0.2855)));
}

Test(scene, shade_in)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	point_light(world.lights, create_point(0, 0.25, 0), create_color(255, 255, 255));
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_elem	*shape = world.objs->next;
	t_inter	i = intersection(0.5, *shape);
	t_comps	comps = prepare_computations(i, r);

	t_rgb	c = shade_hit(&world, comps);

	cr_expect(same_tuple(c, create_color(0.90498, 0.90498, 0.90498)));
}

Test(scene, ray_misses)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 1, 0));

	t_rgb c = color_at(world, r);

	cr_expect(same_tuple(c, create_color(0, 0, 0)));
}

Test(scene, ray_hits)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));

	t_rgb c = color_at(world, r);

	cr_expect(same_tuple(c, create_color(0.38066, 0.47583, 0.2855)));
}

Test(scene, ray_inside)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	t_elem	*outer = world.objs;
	outer->material.ambient = 1.0;
	t_elem	*inner = outer.next;
	inner->material.ambient = 1.0;
	t_ray	r = ray(create_point(0, 0, 0.75), create_vector(0, 0, -1));

	t_rgb c = color_at(world, r);

	cr_expect(same_tuple(c, inner->material.color));
}

Test(scene, default_orientation)
{
	t_point	from = create_point(0, 0, 0);
	t_point	to = create_point(0, 0, -1);
	t_point	up = create_vector(0, 1, 0);

	t_m4x4_f	t = view_transform(from, to, up);
	t_m4x4_f	texpect = identity_matr();

	cr_expect(same_matrix(t, texpect));
}

Test(scene, opposite_orientation)
{
	t_point	from = create_point(0, 0, 0);
	t_point	to = create_point(0, 0, 1);
	t_point	up = create_vector(0, 1, 0);

	t_m4x4_f	t = view_transform(from, to, up);
	t_m4x4_f	texpect = scaling(-1, 1, -1);

	cr_expect(same_matrix(t, texpect));
}

Test(scene, view1)
{
	t_point	from = create_point(0, 0, 8);
	t_point	to = create_point(0, 0, 0);
	t_point	up = create_vector(0, 1, 0);

	t_m4x4_f	t = view_transform(from, to, up);
	t_m4x4_f	texpect = scaling(0, 0, -8);

	cr_expect(same_matrix(t, texpect));
}

Test(scene, view2)
{
	t_point	from = create_point(1, 3, 2);
	t_point	to = create_point(4, -2, 8);
	t_point	up = create_vector(1, 1, 0);

	t_m4x4_f	t = view_transform(from, to, up);
	float tabf4[16] = {-0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857, 0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000};
	t_m4x4_f texpect = matrix_4xf_create(tabf4);

	cr_expect(same_matrix(t, texpect));
}

Test(scene, camera_build)
{
	float	hsize = 160;
	float	vsize = 120;
	//need to remember this is in radian, but we are given degree
	float	fov = M_PI / 2;
	t_camera	c;

	c = setup_camera(hsize, vsize, fov);

	cr_expect(c.hsize == 160);
	cr_expect(c.vsize == 120);
	cr_expect(c.fov == M_PI / 2);
	cr_expect(same_matrix(c.transform, identity_matr()));
}

Test(scene, camera_pixel_size)
{
	t_camera	c = setup_camera(200, 125, M_PI / 2);

	cr_expect(c.pixel_size == 0.01);

	c = setup_camera(125, 200, M_PI / 2);

	cr_expect(c.pixel_size == 0.01);
}

Test(scene, center_ray)
{
	t_camera	c;
	c = setup_camera(201, 101, M_PI / 2);
	t_ray	ray;
	ray = ray_for_pixel(c, 100, 50);

	cr_expect(same_tuple(ray.orig, create_point(0, 0, 0)));
	cr_expect(same_tuple(ray.dest, create_vector(0, 0, -1)));
}

Test(scene, corner_ray)
{
	t_camera	c;
	c = setup_camera(201, 101, M_PI / 2);
	t_ray	ray;
	ray = ray_for_pixel(c, 0, 0);

	cr_expect(same_tuple(ray.orig, create_point(0, 0, 0)));
	cr_expect(same_tuple(ray.dest, create_vector(0.66519, 0.33259, -0.66851)));
}

Test(scene, transformed_ray)
{
	t_camera	c;
	c = setup_camera(201, 101, M_PI / 2);
	t_ray	ray;
	ray = ray_for_pixel(c, 100, 50);
	c.transform = rotation_y(M_PI / 4) * translation(0, -2, 5);
	cr_expect(same_tuple(ray.orig, create_point(0, 2, -5)));
	cr_expect(same_tuple(ray.dest, create_vector(sqrt(2) / 2, 0, -(sqrt(2) / 2))));
}

/* Test(scene, full_scene)
{
	t_scene	w;
	setup_scene(&w, "./scenes/default.rt");
	t_camera	c;
	c = setup_camera(11, 11, M_PI / 2);
	t_float4	from = create_point(0, 0, -5);
	t_float4	to = create_point(0, 0, 0);
	t_float4	up = create_vector(0, 1, 0);
	c.transform = view_transform(from, to, up);
	image = render(c, w);
	cr_expect(same_tuple(pixel_at(image, 5, 5), create_vector(0.38066, 0.47583, 0.2855)));
//	free(image);
} */