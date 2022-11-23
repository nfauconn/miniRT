/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/23 12:55:19 by nfauconn         ###   ########.fr       */
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

//create a ray struct with his origin point & his dest vector
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

//create a struct containing all intersections of a ray with a given obj
// (sphere can only have 2 but maybe more are needed for other objects)
t_tvalues_for_ray	set_tvalues(t_obj obj, uint8_t count, float t1, float t2)
{
	t_tvalues_for_ray	tvalues_for_ray;

	tvalues_for_ray.obj = obj;
	tvalues_for_ray.count = count;
	tvalues_for_ray.t[0] = t1;
	tvalues_for_ray.t[1] = t2;
	return (tvalues_for_ray);
}

//find inter of the given ray with a sphere
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

// add to interlst the new t values found with the given ray
// does not ignore negative t values, as it seems util for chapter 9 with boolean operations
void	add_obj_inters(t_obj obj, t_ray r, t_inter **interlst)
{
	size_t				i;
	t_tvalues_for_ray	tvalues_for_ray;
	t_inter				*inter;

	if (obj.id == sphere)
		tvalues_for_ray = sp_tvalues(obj, r);
	i = 0;
	while (i < tvalues_for_ray.count)
	{
		inter = create_inter(tvalues_for_ray.t[i], obj);
		interaddback(interlst, inter);
		i++;
	}
}

 // find the intersection that has the lowest nonnegative t value
 t_inter	*find_hit(t_inter **interlst)
{
	t_inter	*tmp;
	t_inter	*hit;

	tmp = *interlst;
	hit = tmp;
	while (tmp)
	{
		if (tmp->t >= 0 && tmp->t < hit->t)
			hit = tmp;
		tmp = tmp->next;
	}
	if (hit->t < 0)
		return (NULL);
	return (hit);
}

int	main()
{
	t_point				orig[5] = {{0, 0, -5, pt}, {0, 1, -5, pt}, \
									{0, 2, -5, pt}, 0, {0, 0, 5, pt}};
	size_t				origins_nb = 5;
	size_t				origins_no = 0;
	t_vector			dest = {0, 0, 1, vec};
	t_obj				obj;
	t_inter				*interlst = NULL;
	t_ray				r[origins_nb];
	t_inter				*hit;

	obj = init_sphere();
	while (origins_no < origins_nb)
	{
		r[origins_no] = ray(orig[origins_no], dest);
		add_obj_inters(obj, r[origins_no], &interlst);
		origins_no++;
	}
	hit = find_hit(&interlst);
	free_interlst(&interlst);
	return (0);
}