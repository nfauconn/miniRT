/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:11:12 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/22 18:36:32 by noe              ###   ########.fr       */
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

typedef struct s_inter
{
	float					t;
	t_obj					obj;
	struct s_inter	*next;
}	t_inter;


t_inter	*create_inter(float t, t_obj obj);
void			interaddback(t_inter **head, t_inter *new);
void			free_interlst(t_inter **lst);


#endif