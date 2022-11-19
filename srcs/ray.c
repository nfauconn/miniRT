/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/19 23:40:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

t_obj	init_sphere() //will be added some atributes later in the chapter
{
	t_obj			s;
	static ssize_t	no = -1;

	no++;
	s.id = sphere;
	s.no = no;
	s.center = (t_point){0, 0, 0};
	return(s);
}

t_ray	ray(t_point orig, t_vector dest)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dest = dest;
	return (ray);
}

/* position after t iterations of vector r.dest on point r.origin
=>> util for light and shading
--> turning intersections into actual surface informations */
t_point	position(t_ray ray, float t)
{
	return (ray.orig + ray.dest * t);
}

t_tvalues_for_ray	set_tvalues(t_obj obj, uint8_t count, float t1, float t2)
{
	t_tvalues_for_ray	tvalues_for_ray;

	tvalues_for_ray.obj = obj;
	tvalues_for_ray.count = count;
	tvalues_for_ray.t[0] = t1;
	tvalues_for_ray.t[1] = t2;
	return (tvalues_for_ray);
}

t_tvalues_for_ray sp_tvalues(t_obj s, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t1;
	float		t2;

	sphere_to_ray = r.orig - s.center;
	a = dot3(r.dest, r.dest);
	b = 2 * dot3(r.dest, sphere_to_ray);
	c = dot3(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (set_tvalues(s, 0, 0, 0));
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	return (set_tvalues(s, 2, t1, t2));
}

t_tvalues_for_ray	tvalues_for_ray(t_obj obj, t_ray r)
{
	t_tvalues_for_ray	tvalues_for_ray;

//	if (obj.id == sphere)
		tvalues_for_ray = sp_tvalues(obj, r);
	return (tvalues_for_ray);
}

int	main()
{
	size_t				i = 0;
	t_point				orig[5] = {{0, 0, -5}, {0, 1, -5}, {0, 2, -5}, 0, {0, 0, 5}};
	size_t				origins_nb = 5;
	size_t				origins_no = 0;
	t_vector			dest = {0, 0, 1};
	t_obj				s = init_sphere();
	t_intersection		*interlst = NULL;

	t_ray				r[origins_nb];
	t_tvalues_for_ray	tvals[origins_nb];
	t_intersection		*inter;

	while (origins_no < origins_nb)
	{
		r[origins_no] = ray(orig[origins_no], dest);
		tvals[origins_no] = tvalues_for_ray(s, r[origins_no]);
		while (i < tvals[origins_no].count)
		{
			if (tvals[origins_no].t[i] > 0)
			{
				inter = create_intersection(tvals[origins_no].t[i], s);
				interaddback(&interlst, inter);
			}
			i++;
		}
		i = 0;
		origins_no++;
	}

	free_interlst(&interlst);
	return (0);
}