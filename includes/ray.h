/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:11:12 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/10 13:15:04 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H

# include "minirt.h"
# include "tuple.h"

typedef struct s_ray
{
	t_point		orig;
	t_point		dest;
}	t_ray;

typedef struct s_xs
{
	size_t		count;
	float		t[2];
	t_elem		obj;
}	t_xs;

typedef struct s_inter
{
	float				t;
	t_elem				obj;
	t_point				point;
	t_vector			eyev;
	t_vector			normalv;
	bool				inside;
	struct s_inter		*next;
}	t_inter;

/* RAY */
t_ray		ray(t_point orig, t_vector dest);
t_point		position(t_ray ray, float t);

/* SPHERE */
void		init_sphere(t_elem *s);
t_xs		sp_xs(t_elem s, t_ray r);

/* INTERSECTION */
t_xs		intersect(t_elem obj, t_ray r);
t_inter		intersection(float t, t_elem obj);
t_inter		hit(t_xs xs);

/* INTERS LIST */
void		add_obj_inters(t_xs xs, t_inter **interlst);
t_inter		*create_inter(float t, t_elem obj);
void		interaddback(t_inter **head, t_inter *new);
t_inter		*find_hit(t_inter **interlst);
void		free_interlst(t_inter **lst);

/* TRANFORM */
t_ray		transform_ray(t_ray prev_r, t_m4x4_f matrix);
void		set_transform(t_elem *obj, t_m4x4_f transfo_matrix);

#endif