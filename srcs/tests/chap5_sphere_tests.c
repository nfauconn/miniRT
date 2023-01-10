/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap5_sphere_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:32:43 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/10 19:09:49 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mycriterion.h"
#include "matrix.h"
#include "externlibs.h"
#include "tuple.h"
#include "setup.h"
#include "ray.h"
#include "inter.h"

Test (ray, create)
{
	t_float4	ori = create_point(1, 2, 3);
	t_float4	dir = create_vector(4, 5, 6);

	t_ray	r = ray(ori, dir);
	cr_expect(same_tuple(r.orig, ori));
	cr_expect(same_tuple(r.orig, ori) == 1);
}

Test (ray, create2)
{
	t_float4	ori = create_point(2, 3, 4);
	t_float4	dir = create_vector(1, 0, 0);

	t_ray	r = ray(ori, dir);
	t_float4	p1 = position(r, 0);
	// printf ("%f, %f, %f, %f\n", p1.x, p1.y, p1.z, p1.w);
	t_float4	p2 = position(r, 1);
	t_float4	p3 = position(r, -1);
	t_float4	p4 = position(r, 2.5);

	cr_expect(same_tuple(p1, create_point(2, 3, 4)));
	cr_expect(same_tuple(p2, create_point(3, 3, 4)));
	cr_expect(same_tuple(p3, create_point(1, 3, 4)));
	cr_expect(same_tuple(p4, create_point(4.5, 3, 4)));
}

Test (ray, intersect1)
{
	t_ray	r = ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	t_elem	s;
	init_sphere(&s);
	t_xs	xs = intersect(&s, r);

	cr_expect(xs.count == 2);
	cr_expect(same_float(xs.t[0], 4.0));
	cr_expect(same_float(xs.t[1], 6.0));

	r = ray(create_point(0, 1, -5), create_vector(0, 0, 1));
	xs = intersect(&s, r);

	cr_expect(xs.count == 2);
	cr_expect(same_float(xs.t[0], 5.0));
	cr_expect(same_float(xs.t[1], 5.0));

	r = ray(create_point(0, 2, -5), create_vector(0, 0, 1));
	s.transform = identity_matr();
	xs = intersect(&s, r);

	cr_expect(xs.count == 0);
	cr_expect(same_float(xs.t[0], 0.0));
	cr_expect(same_float(xs.t[1], 0.0));

	r = ray(create_point(0, 0, 0), create_vector(0, 0, 1));
	xs = intersect(&s, r);

	cr_expect(xs.count == 2);
	cr_expect(same_float(xs.t[0], -1.0));
	cr_expect(same_float(xs.t[1], 1.0));

	r = ray(create_point(0, 0, 5), create_vector(0, 0, 1));
	xs = intersect(&s, r);

	cr_expect(xs.count == 2);
	cr_expect(same_float(xs.t[0], -6.0));
	cr_expect(same_float(xs.t[1], -4.0));

	t_inter	i1 = intersection(3.5, &s);

	cr_expect(same_float(i1.t, 3.5));
	cr_expect(i1.obj->id.shape == s.id.shape);
	cr_expect(i1.obj->id.no == s.id.no);
}

// Test (ray, intersection_aggreg)
// {
// 	t_elem
//  init_sphere(&s);	s;
// 	t_inter	i1 = intersection(1, s);
// 	t_inter	i2 = intersection(2, s);

// 	t_xs	xs= intersections(i1, i2);
// 	cr_expect(xs.count == 2);
// 	cr_expect(same_float(xs.t[0], 1.0));
// 	cr_expect(same_float(xs.t[1], 2.0));
// }