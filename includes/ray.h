/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:11:12 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/23 18:20:20 by nfauconn         ###   ########.fr       */
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

typedef struct s_obj
{
	uint8_t		id;
	ssize_t		no;
	t_point		center;
}	t_obj;

typedef struct s_tvalues_for_ray
{
	size_t		count;
	float		t[2];
	t_obj		obj;
}	t_tvalues_for_ray;

typedef struct s_inter
{
	float					t;
	t_obj					obj;
	struct s_inter	*next;
}	t_inter;


t_inter				*create_inter(float t, t_obj obj);
void				interaddback(t_inter **head, t_inter *new);
void				free_interlst(t_inter **lst);
t_obj				init_sphere(void);
t_ray				ray(t_point orig, t_vector dest);
t_point				position(t_ray ray, float t);
t_tvalues_for_ray	set_tvalues(t_obj obj, uint8_t count, float t1, float t2);
t_tvalues_for_ray	sp_tvalues(t_obj s, t_ray r);
void				add_obj_inters(t_obj obj, t_ray r, t_inter **interlst);
t_inter				*find_hit(t_inter **interlst);

#endif