/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap7_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:29:05 by rokerjea          #+#    #+#             */
/*   Updated: 2024/02/06 12:19:30 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "criterion_utils.h"

void	print_tuple(t_float4 var);

t_material	test_default_material(t_elem *elem);

t_material	test_default_material2(t_elem *elem)
{
	t_material	material;

	material.color = elem->color;
	material.ambient = 0.1;
	material.diffuse = 0.7;
	material.specular = 0.2;
	material.shininess = 200.0;
	return (material);
}

Test(scene, world)
{
	t_scene	world;
	setup_scene(&world, "./scenes/TESTempty.rt");
	cr_expect(world.objs == NULL);
	cr_expect(world.lights == NULL);
	clear (&world);
}

Test(scene, setup2sp)
{
	t_scene	world;
	t_elem	*sp;
	t_rgb	color;
	t_m4x4_f	transform;

	setup_scene(&world, "./scenes/TEST2spheres1light.rt");
	sp = world.objs;
	color = create_color(0.8, 1.0, 0.6);

	cr_expect(same_tuple(world.lights->color, (t_float4){1, 1, 1, 0}));
	cr_expect(same_tuple(world.lights->w_pos, (t_float4){-10, 10, -10, 1}));
	cr_expect(same_tuple(sp->color, color));

	sp = sp->next;
	transform = scaling(0.5, 0.5, 0.5);
	set_transform(sp, transform);
	cr_expect(same_matrix(sp->transform, transform));
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
	t_ray	r;
	t_xs	xs;

	setup_scene(&world, "./scenes/TEST2spheres1light.rt");
	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	xs = intersect(world.objs, r);
	cr_expect(same_float(xs.t[0], 4.0));
	clear (&world);
}

Test(scene, precompute)
{
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_elem	shape;
	init_sphere(&shape);
	t_inter	i = intersection(4, &shape);
	prepare_computations(&i, r);
	cr_expect(same_float(i.t, i.t) == 1);
	cr_expect(same_tuple(i.point , create_point(0, 0, -1)));
	cr_expect(same_tuple(i.eyev , create_vector(0, 0, -1)));
	cr_expect(same_tuple(i.normalv , create_vector(0, 0, -1)));
}

Test(scene, outside)
{
	//t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	//t_elem	shape;
	//init_sphere(&shape);
	//t_inter	i = intersection(4, &shape);
	//prepare_computations(&i, r);
	//cr_expect(!i.inside);
}

Test(scene, inside)
{
	t_ray	r = ray(create_point(0, 0, 0), create_vector(0, 0, 1));
	t_elem	shape;
	init_sphere(&shape);
	shape.transform = identity_matr();
	t_inter	i = intersection(1, &shape);
	prepare_computations(&i, r);
	cr_expect(same_tuple(i.point , create_point(0, 0, 1)));
	cr_expect(same_tuple(i.eyev , create_vector(0, 0, -1)));
	cr_expect(i.inside);
	cr_expect(same_tuple(i.normalv , create_vector(0, 0, -1)));
}

Test(scene, shade_hit)
{
	t_scene	world;
	t_elem	*shape;
	t_elem	*shape2;

	setup_scene(&world, "./scenes/TEST2spheres1light.rt");
	shape = world.objs;
	shape2 = world.objs->next;
	shape->material = test_default_material2(shape);
	shape2->material = test_default_material(shape2);
	shape2->transform = scaling(0.5, 0.5, 0.5);

	clear(&world);
}

// important : fonction color_at, qui determine couleur du pixel touche par le ray
 Test(scene, color_at)
{
	t_scene	world;
	t_ray	r;
	t_rgb	c;

	setup_scene(&world, "./scenes/TEST2spheres1light.rt");
	world.amblight->color = create_color(1, 1, 1);
	world.amblight->specs.ratio = 1;
	world.objs->material = test_default_material2(world.objs);
	world.objs->next->material = test_default_material(world.objs->next);
	world.objs->next->transform = scaling(0.5, 0.5, 0.5);

	// ray misses
	r = ray(create_point(0, 0, -5), create_vector(0, 1, 0));
	c = color_at(&world, r);
	cr_expect(same_tuple(c, create_color(0, 0, 0)));

/* 	// ray hits
	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	c = color_at(&world, r);
	cr_expect(same_tuple(c, create_color(0.38066, 0.47583, 0.2855))); */

	world.objs->next->material.ambient = 1.0;
	r = ray(create_point(0, 0, 0.75), create_vector(0, 0, -1));
	c = color_at(&world, r);
	cr_expect(same_tuple(c, world.objs->next->material.color));
	world.objs->next->material = test_default_material(world.objs->next);

	clear(&world);
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
	t_m4x4_f	texpect = translation(0, 0, -8);

	cr_expect(same_matrix(t, texpect));
}

Test(scene, view2)
{
//	t_point	from = create_point(1, 3, 2);
//	t_point	to = create_point(4, -2, 8);
//	t_point	up = create_vector(1, 1, 0);

//	t_m4x4_f	t = view_transform(from, to, up);
//	float tabf4[16] = {-0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857, 0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000};
//	t_m4x4_f texpect = matrix_4xf_create(tabf4);

//	cr_expect(same_matrix(t, texpect));
}

Test(scene, camera_pixel_size)
{
	t_scene		scene;
	float		hsize;
	float		vsize;
	t_ray		ray;
/* 	t_point		from;
	t_point		to;
	t_point		up; */

	setup_scene(&scene, "./scenes/TEST2spheres1light.rt");

	hsize = 160;
	vsize = 120;
	init_camera(scene.cam, hsize, vsize);
	scene.cam->transform = identity_matr();
	cr_expect(scene.cam->hsize == 160);
	cr_expect(scene.cam->vsize == 120);
	cr_expect(same_float(scene.cam->fov, M_PI / 2));
	cr_expect(same_matrix(scene.cam->transform, identity_matr()));

	hsize = 200;
	vsize = 125;
	init_camera(scene.cam, hsize, vsize);
	cr_expect(same_float(scene.cam->pixel_size, 0.01));

	hsize = 201;
	vsize = 101;
	init_camera(scene.cam, hsize, vsize);
	ray = ray_for_pixel(*scene.cam, 100, 50);
	cr_expect(same_tuple(ray.orig, create_point(0, 0, 0)));
	cr_expect(same_tuple(ray.dir, create_vector(0, 0, -1)));

	hsize = 201;
	vsize = 101;
	init_camera(scene.cam, hsize, vsize);
	ray = ray_for_pixel(*scene.cam, 0, 0);
	cr_expect(same_tuple(ray.orig, create_point(0, 0, 0)));
	cr_expect(same_tuple(ray.dir, create_vector(0.66519, 0.33259, -0.66851)));

	scene.cam->transform = rotation_y(M_PI / 4) * translation(0, -2, 5);
	ray = ray_for_pixel(*scene.cam, 100, 50);
	cr_expect(same_tuple(ray.orig, create_point(0, 2, -5)));
	cr_expect(same_tuple(ray.dir, create_vector(sqrt(2) / 2, 0, -sqrt(2) / 2)));

/* 	hsize = 11;
	vsize = 11;
	init_camera(scene.cam, hsize, vsize);
	from = create_point(0, 0, -5);
	to = create_point(0, 0, 0);
	up = create_vector(0, 1, 0);
	scene.cam->transform = view_transform(from, to, up);
	image = render(c, w);
	cr_expect(same_tuple(pixel_at(image, 5, 5), create_vector(0.38066, 0.47583, 0.2855))); */

  	clear(&scene);
}
