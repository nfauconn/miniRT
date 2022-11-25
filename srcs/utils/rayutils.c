/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:08:51 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/25 20:21:09 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "matrix.h"

/* create a ray struct with his origin point & his dest vector */
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

t_obj	init_sphere(void)
{
	t_obj			s;
	static ssize_t	no = -1;

	no++;
	s.id = sphere;
	s.no = no;
	s.center = (t_point){0, 0, 0};
	s.transform = identity_matr();
	return (s);
}

/*  find the intersection that has the lowest nonnegative t value*/
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

t_inter	*create_inter(float t, t_obj obj)
{
	t_inter	*i;

	i = malloc(sizeof(t_inter));
	if (!i)
		return (NULL);
	i->t = t;
	i->obj = obj;
	return (i);
}

void	interaddback(t_inter **head, t_inter *new)
{
	t_inter	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
}

void	free_interlst(t_inter **lst)
{
	t_inter	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free);
	}
}