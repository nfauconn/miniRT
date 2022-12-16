/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:32:28 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/16 13:33:02 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

void	init_sphere(t_elem *s)
{
	static ssize_t	no = -1;

	no++;
	s->id.shape = sphere;
	s->id.no = no;
	s->o_pos = create_point(0, 0, 0);
	s->transform = identity_matr();
	s->material = default_material(s);
}

int	set_sphere(t_scene *scene, char **params)
{
	int		ret;
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
