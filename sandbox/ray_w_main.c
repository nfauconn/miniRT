/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_w_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/25 20:25:29 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"

/* find inter of the given ray with a sphere */
t_xs	sp_xs(t_obj s, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_xs		xs;

	sphere_to_ray = r.orig - s.center;
	a = dot3(r.dest, r.dest);
	b = 2 * dot3(r.dest, sphere_to_ray);
	c = dot3(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
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

t_ray	transform_ray(t_ray prev_r, t_m4x4_f matrix)
{
	t_ray	r;

	r.orig = matrix_tuple_mult(matrix, prev_r.orig);
	r.dest = matrix_tuple_mult(matrix, prev_r.dest);
	return (r);
}

t_obj	set_transform(t_obj obj, t_m4x4_f transfo_matrix)
{
	obj.transform = transfo_matrix;
	return (obj);
}

/* INTERSECT
** create a struct containing all intersections of a ray with a given obj
** (sphere can only have 2 but maybe more are needed for other objects) */
t_xs	intersect(t_obj obj, t_ray r)
{
	t_xs	xs;

	r = transform_ray(r, inversion(obj.transform));
	ft_bzero(&xs, sizeof(xs));
	if (obj.id == sphere)
		xs = sp_xs(obj, r);
	xs.obj = obj;
	return (xs);
}

/* add to interlst the new t values found with the given ray
   does not ignore negative t values, as it seems util for chapter 9
   with boolean operations */
void	add_obj_inters(t_obj obj, t_ray r, t_inter **interlst)
{
	size_t				i;
	t_xs	xs;
	t_inter				*inter;

	xs = intersect(obj, r);
	i = 0;
	while (i < xs.count)
	{
		inter = create_inter(xs.t[i], obj);
		interaddback(interlst, inter);
		i++;
	}
}

int	main(void)
{
	t_point				orig[6] = {{0, 0, -5, pt}, {0, 1, -5, pt}, \
									{0, 2, -5, pt}, 0, {0, 0, 5, pt}, \
									{1, 2, 3, pt}};
	size_t				origins_nb = 6;
//	size_t				origins_no = 0;
	t_vector			dest[2] = {{0, 0, 1, vec}, {0, 1, 0, vec}};
	t_obj				obj;
	t_inter				*interlst = NULL;
	t_ray				r[origins_nb];
//	t_ray				r2[origins_nb];
//	t_inter				*hit;

	obj = init_sphere();
	obj = set_transform(obj, scaling(2, 2, 2));
/* 	while (origins_no < origins_nb)
	{
		r[origins_no] = ray(orig[origins_no], dest[0]);
		add_obj_inters(obj, r[origins_no], &interlst);
		origins_no++;
	} */
//	hit = find_hit(&interlst);
//	r2[0] = transform_ray(r[5], translation(3, 4, 5));
//	r2[0] = transform_ray(r[5], scaling(2, 2, 2));
	r[0] = ray(orig[0], dest[0]);
	add_obj_inters(obj, r[0], &interlst);
	free_interlst(&interlst);
	return (0);
}