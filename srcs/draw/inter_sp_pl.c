/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sp_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:46:15 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:18:22 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter.h"

/* find inter of the given ray with a sphere */
t_xs	sp_intersect(t_elem s, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		discriminant;
	t_xs		xs;

	sphere_to_ray = r.orig - s.o_pos;
	a = dot_product(r.dir, r.dir);
	b = 2 * dot_product(r.dir, sphere_to_ray);
	discriminant = pow(b, 2) - 4 * a * (dot_product(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		ft_bzero(&xs, sizeof(xs));
	else
	{
		xs.count = 2;
		xs.t[0] = (-b - sqrt(discriminant)) / (2 * a);
		xs.t[1] = (-b + sqrt(discriminant)) / (2 * a);
	}
	return (xs);
}

t_xs	pl_intersect(t_elem p, t_ray r)
{
	t_xs	xs;

	(void)p;
	if (fabsf(r.dir.y) < EPSILON)
		xs.count = 0;
	else
	{
		xs.count = 1;
		xs.t[0] = -r.orig.y / r.dir.y;
	}
	return (xs);
}
