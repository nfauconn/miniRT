/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:42:12 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 15:44:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter.h"

float	cylinder_min(t_elem cyl)
{
	float	min;

	min = 0 + cyl.w_pos.y;
	return (min);
}

float	cylinder_max(t_elem cyl)
{
	float	max;

	max = cyl.specs.diam_hght[1] + cyl.w_pos.y;
	return (max);
}

static t_xs	cylinder_limits(t_elem cyl, t_ray ray, t_xs xs)
{
	float	ymin;
	float	ymax;
	float	y0;
	float	y1;

	ymax = cylinder_max(cyl);
	ymin = cylinder_min(cyl);
	y0 = ray.orig.y + (xs.t[0] * ray.dir.y);
	if (y0 <= ymin || y0 >= ymax)
	{
		xs.count--;
		xs.t[0] = xs.t[1];
	}
	y1 = ray.orig.y + (xs.t[1] * ray.dir.y);
	if (y1 <= ymin || y1 >= ymax)
	{
		xs.count--;
		xs.t[1] = -1;
	}
	return (xs);
}

t_xs	local_intersect_cyl(t_elem cyl, t_ray ray)
{
	t_xs	xs;
	float	a;
	float	b;
	float	c;
	float	disc;

	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	b = (2 * ray.orig.x * ray.dir.x) + (2 * ray.orig.z * ray.dir.z);
	c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1;
	disc = (b * b) - (4 * a * c);
	if (disc < 0 || (a > -0.001 && a < 0.001))
		ft_bzero(&xs, sizeof(xs));
	else
	{
		xs.count = 2;
		xs.t[0] = (-b - sqrt(disc)) / (2 * a);
		xs.t[1] = (-b + sqrt(disc)) / (2 * a);
		xs = cylinder_limits(cyl, ray, xs);
	}
	return (xs);
}
