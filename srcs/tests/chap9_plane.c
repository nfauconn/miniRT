/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap9_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:48 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 18:29:13 by nfauconn         ###   ########.fr       */
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