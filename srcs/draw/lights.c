/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:21:52 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/12 16:1 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	t_vector	reflect;

	reflect = in - normal * 2 * dot_product(in, normal);
	return (reflect);
}

void	compute_diffuse(t_lighting *l, t_inter inter)
{
	l->diffuse = l->effective_color * inter.obj->material.diffuse \
														* l->cos_lightv_normalv;
	l->reflectv = reflect(-l->lightv, inter.normalv);
	l->cos_reflectv_eyev = dot_product(l->reflectv, inter.eyev);
}

void	compute_specular(t_lighting *l, t_inter inter, t_elem *light)
{
	l->factor = pow(l->cos_reflectv_eyev, inter.obj->material.shininess);
	l->specular = light->color * inter.obj->material.specular * l->factor;
}

void	compute_ambient(t_lighting *l, t_inter inter, t_elem *light, t_scene *s)
{
	l->effective_color = inter.obj->material.color * light->color;
	l->lightv = normalize(light->w_pos - inter.over_point);
	l->ambient = l->effective_color * s->amblight->color;
	l->cos_lightv_normalv = dot_product(l->lightv, inter.normalv);
}

t_rgb	lighting(t_scene *scene, t_elem *light, t_inter inter, bool shadowed)
{
	t_rgb		res;
	t_lighting	l;

	ft_bzero(&l, sizeof (t_lighting));
	compute_ambient(&l, inter, light, scene);
	if (l.cos_lightv_normalv >= 0)
	{
		compute_diffuse(&l, inter);
		if (l.cos_reflectv_eyev > 0)
			compute_specular(&l, inter, light);
	}
	if (shadowed)
		res = l.ambient;
	else
		res = l.ambient + l.diffuse + l.specular;
	return (res);
}
