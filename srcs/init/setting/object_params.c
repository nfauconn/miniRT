/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:03:30 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/15 20:27:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

t_material	default_material(t_elem *elem)
{
	t_material	material;

	material.color = elem->color;
	material.ambient = 0.1;
	material.diffuse = 0.7;
	material.specular = 0.3;
	material.shininess = 200.0;
	return (material);
}

void	change_obj_transform_matr(t_elem *obj)
{
	if (obj->shape == sphere)
		obj->transform = sp_transform_matr(obj);
	else if (obj->shape == cylinder)
		obj->transform = cyl_transfo_matr(obj);
	else if (obj->shape == plane)
		obj->transform = pl_transform_matr(obj);
}

void	change_cam_transform_matr(t_camera *cam)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	from = cam->w_pos;
	to = cam->orientation;
	up = create_vector(0, 1, 0);
	cam->transform = view_transform(from, to, up);
}
