/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:32:28 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/11 14:30:40 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

t_m4x4_f	sp_transform_matr(t_elem *s)
{
	t_m4x4_f	res;

	res = matrix_mult(translation(s->w_pos.x, s->w_pos.y, s->w_pos.z), \
					scaling(s->specs.radius, s->specs.radius, s->specs.radius));
	return (res);
}

void	init_sphere(t_elem *s)
{
	s->shape = sphere;
	s->o_pos = create_point(0, 0, 0);
	s->transform = sp_transform_matr(s);
	s->material = default_material(s);
}

int	set_sphere(t_scene *scene, char **params)
{
	int			ret;
	t_elem		*newsphere;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for sphere"));
	newsphere = ft_calloc(1, sizeof(t_elem));
	if (!newsphere)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newsphere, params[0])
		|| conv_radius(params[2], newsphere, params[0])
		|| conv_rgb(params[3], newsphere, params[0]))
		ret = 1;
	init_sphere(newsphere);
	elem_add_back(&scene->objs, newsphere);
	return (ret);
}
