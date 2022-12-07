/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap7_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:29:05 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/07 16:54:02 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"
#include "matrix.h"
#include "minirt.h"
#include "extern_libs.h"
#include "tuple.h"
#include "ray.h"

Test(scene, world)
{
	t_scene	world;
	setup_scene(&world, "./scenes/empty.rt");
	cr_expect(world.objs == NULL);
	cr_expect(world.lights == NULL);
	clear (&world);
}

// Test(scene, nom)
// {
// 	//ARRANGE

// 	//ACT

// 	//ASSERT
// 	cr_expect()
// }

t_float4	create_point(float x, float y, float z)
{
	t_float4	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 1.0;
	return (point);
}

t_float4	create_vector(float x, float y, float z)
{
	t_float4	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 0.0;
	return (point);
}

Test(scene, default)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	cr_expect(same_tuple(world.lights->color, (t_float4){255, 255, 255, 0}));
	cr_expect(same_tuple(world.lights->pos, (t_float4){-10, 10, -10, 1}));
	t_elem	sp = *world.objs;
	t_float4	color = create_vector(204, 255, 153);
	cr_expect(same_tuple(sp.color, color));
	sp = *sp.next;
	t_m4x4_f	transform = scaling(0.5, 0.5, 0.5);
	sp = set_transform(sp, transform);
	cr_expect(same_matrix(sp.transform, transform));
	// printf_4fmatr(transform);
	// printf_4fmatr(sp.transform);
	clear (&world);
}

int	nearer_point(t_xs res, t_xs newres)
{
	if(newres.t[0] >= 0)
	{
		if(newres.t[0] < res.t[0] && newres.t[0] < res.t[1])
		return (1);
	}
	if(newres.t[1] >= 0)
	{
		if(newres.t[1] < res.t[0] && newres.t[1] < res.t[1])
		return (1);
	}
	return (0);
}

t_xs	intersect_world(t_scene world, t_ray ray)
{
	t_elem	shape;
	t_xs	res;
	// t_xs	new_res;

	shape = *world.objs;
	res = intersect(shape, ray);
	printf("%f\n", res.t[0]);
	printf("%f\n", res.t[1]);
	// while (shape.next != NULL)
	// {
	// 	new_res = intersect(shape, ray);
	// 	if (nearer_point(res, new_res))
	// 		res = new_res;
	// 	shape = *shape.next;
	// }
	// if (res.t[1] >= 0 && res.t[1] < res.t[0])
	// 	res.t[0] = res.t[1];
	return (res);
}

void	print_tuple(t_float4 var)
{
	printf("%f, %f, %f, %f \n", var.x, var.y, var.z, var.w);
}

void	print_shape(t_elem *shape)
{
	printf("center = ");
	print_tuple(shape->center);
	printf("pos = ");
	print_tuple(shape->pos);
	printf("color = ");
	print_tuple(shape->color);
	printf("specs = %f\n", shape->specs.radius);
}

Test(scene, world_ray)
{
	t_scene	world;
	setup_scene(&world, "./scenes/default.rt");
	world.objs->transform = identity_matr();
	print_shape(world.objs);
	t_ray r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_xs	intelist = intersect(*world.objs, r);
	cr_expect(same_float(intelist.t[0], 4.0));
	printf("%f\n", intelist.t[0]);
	printf("%f\n", intelist.t[1]);
	clear (&world);
}

// Test(scene, precompute)