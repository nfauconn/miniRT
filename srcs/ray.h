/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:11:12 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/19 23:15:48 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H

#include "minirt.h"

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

typedef struct s_intersection
{
	float					t;
	t_obj					obj;
	struct s_intersection	*next;
}	t_intersection;


t_intersection	*create_intersection(float t, t_obj obj);
void			interaddback(t_intersection **head, t_intersection *new);
void			free_interlst(t_intersection **lst);


#endif