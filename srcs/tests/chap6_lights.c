/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap6_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:29:49 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/13 15:59:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "criterion_utils.h"

//	printf("normal = {%f, %f, %f, %f}\normal", normal.x, normal.y, normal.z, normal.w);

t_material	test_default_material(t_elem *elem)
{
	t_material	material;

	material.color = elem->color;
	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;
	return (material);
}

void	print_tuple(t_float4 var)
{
	printf("{%f, %f, %f, %f}\n", var.x, var.y, var.z, var.w);
}

Test(lights, normal_1)
{
	t_elem		sp;
	t_vector	normal;

	init_sphere(&sp);
	sp.transform = identity_matr();

	normal = normal_at(&sp, create_point(1, 0, 0));
	cr_expect(same_tuple(normal, create_vector(1, 0, 0)));

	normal = normal_at(&sp, create_point(0, 1, 0));
	cr_expect(same_tuple(normal, create_vector(0, 1, 0)));

	normal = normal_at(&sp, create_point(0, 0, 1));
	cr_expect(same_tuple(normal, create_vector(0, 0, 1)));

	normal = normal_at(&sp, create_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
	cr_expect(same_tuple(normal, create_vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)));
}

Test(lights, normal_translated_sp)
{
	t_elem		sp;
	t_point		w_pt;
	t_vector	w_normal;
	t_m4x4_f	transfo_mx;

	init_sphere(&sp);
	transfo_mx = translation(0, 1, 0);
	set_transform(&sp, transfo_mx);
	w_pt = create_point(0, 1.70711, -0.70711);
	w_normal = normal_at(&sp, w_pt);
	cr_expect(same_tuple(w_normal, create_vector(0, 0.70711, -0.70711)));
}

Test(lights, normal_transformed_sp)
{
	t_elem		sp;
	t_point		w_pt;
	t_vector	w_normal;
	t_m4x4_f	transfo_mx;

	init_sphere(&sp);
	transfo_mx = scaling(1, 0.5, 1) * rotation_z(M_PI/5);
	set_transform(&sp, transfo_mx);
	w_pt = create_point(0, sqrt(2)/2, -sqrt(2)/2);
	w_normal = normal_at(&sp, w_pt);
	cr_expect(same_tuple(w_normal, create_vector(0, 0.97014, -0.24254)));
}

/* Reflecting a vector approaching the normal at 45° */
Test(lights, find_reflecting_vector)
{
	t_vector	v;
	t_vector	n;
	t_vector	r;

	v = create_vector(1, -1, 0);
	n = create_vector(0, 1, 0);
	r = reflect(v, n);
	cr_expect(same_tuple(r, create_vector(1, 1, 0)));

	v = create_vector(0, -1, 0);
	n = create_vector(sqrt(2)/2, sqrt(2)/2, 0);
	r = reflect(v, n);
	cr_expect(same_tuple(r, create_vector(1, 0, 0)));
}

Test(lights, get_lighting)
{
	t_scene		scene;
	t_elem		light;
	t_inter		inter;
	t_rgb		res;

	setup_scene(&scene, "./scenes/TESTempty.rt");
	light.color = (t_rgb)WHITE;
	light.specs.ratio = 1;
	light.material = test_default_material(&light);
	inter.obj = &light;
	inter.over_point = create_point(0, 0, 0);

/*	lighting with the eye btw the light and the surface, eye offset 90° (perpendicular to surface) */
	inter.eyev = create_vector(0, 0, -1);
	inter.normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 0, -10), (t_rgb)WHITE);
	res = lighting(&scene, &light, inter, 0);
	cr_expect(same_tuple(res, create_color(1.9, 1.9, 1.9)));

/*	lighting with the eye btw light & surface, eye offset 45°*/
	inter.eyev = create_vector(0, sqrt(2)/2, -sqrt(2)/2);
	inter.normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 0, -10), (t_rgb)WHITE);
	res = lighting(&scene, &light, inter, 0);
	cr_expect(same_tuple(res, create_color(1.0, 1.0, 1.0)));

/*	lighting with eye offset 90° , light offset 45°*/
	inter.eyev = create_vector(0, 0, -1);
	inter.normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 10, -10), (t_rgb)WHITE);
	res = lighting(&scene, &light, inter, 0);
	cr_expect(same_tuple(res, create_color(0.7364, 0.7364, 0.7364)));

/*	lighting with the eye in the path of the reflection vector */
	inter.eyev = create_vector(0, -sqrt(2)/2, -sqrt(2)/2);
	inter.normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 10, -10), (t_rgb)WHITE);
	res = lighting(&scene, &light, inter, 0);
//	printf("lighting = {%f, %f, %f, %f}\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(res, create_color(1.636385, 1.636385, 1.636385)));

/*	lighting with the light behind the surface and light beyond */
	inter.eyev = create_vector(0, 0, -1);
	inter.normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 0, 10), (t_rgb)WHITE);
	res = lighting(&scene, &light, inter, 0);
	cr_expect(same_tuple(res, create_color(0.1, 0.1, 0.1)));
}