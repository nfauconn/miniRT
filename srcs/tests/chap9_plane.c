/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap9_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:48 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 19:22:25 by nfauconn         ###   ########.fr       */
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

Test(plane, constant_normal)
{
	t_vector	n1;
	t_vector	n2;
	t_vector	n3;
	t_elem		p;

	init_plane(&p);
	n1 = normal_at(&p, create_point(0, 0, 0));
	n2 = normal_at(&p, create_point(10, 0, -10));
	n3 = normal_at(&p, create_point(-5, 0, 150));

	cr_expect(same_tuple(n1, create_vector(0, 1, 0)));
	cr_expect(same_tuple(n2, create_vector(0, 1, 0)));
	cr_expect(same_tuple(n3, create_vector(0, 1, 0)));
}

Test(plane, intersect)
{
	t_elem	p;
	t_ray	r;
	t_xs	xs;

	init_plane(&p);

	/* intersect with a ray parallel to the plane */
	r = ray(create_point(0, 10, 0), create_vector(0, 0, 1));
	xs = intersect(p, r);
	cr_expect(xs.count == 0);

	/* intersect with a coplanar ray */
	r = ray(create_point(0, 0, 0), create_vector(0, 0, 1));
	xs = intersect(p, r);
	cr_expect(xs.count == 0);

	/* intersect a plane from below */
	r = ray(create_point(0, 1, 0), create_vector(0, -1, 0));
	xs = intersect(p, r);
	cr_expect(xs.count == 1);
	cr_expect(xs.t[0] == 1);

	/* intersect a plane from above */
	r = ray(create_point(0, -1, 0), create_vector(0, 1, 0));
	xs = intersect(p, r);
	cr_expect(xs.count == 1);
	cr_expect(xs.t[0] == 1);
}