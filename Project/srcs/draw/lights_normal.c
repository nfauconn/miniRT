/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:06:03 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:06:42 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_vector	cylinder_normal(t_elem cyl, t_point local_pt)
{
	float		dist;
	t_vector	local_normal;

	dist = (local_pt.x * local_pt.x) + (local_pt.z * local_pt.z);
	if (dist < 1 && local_pt.y >= (cylinder_max(cyl) - EPSILON))
		local_normal = create_vector(0, 1, 0);
	else if (dist < 1 && local_pt.y <= (cylinder_min(cyl) + EPSILON))
		local_normal = create_vector(0, -1, 0);
	else
		local_normal = create_vector(local_pt.x, 0, local_pt.z);
	return (local_normal);
}

t_vector	normal_at(t_elem *obj, t_point w_pt)
{
	t_point		local_pt;
	t_vector	local_normal;
	t_vector	w_normal;

	local_pt = matrix_tuple_mult(inverse(obj->transform), w_pt);
	if (obj->shape == sphere)
		local_normal = local_pt - obj->o_pos;
	if (obj->shape == plane)
		local_normal = create_vector(0, 1, 0);
	if (obj->shape == cylinder)
		local_normal = cylinder_normal(*obj, local_pt);
	w_normal = matrix_tuple_mult(transpose(inverse(obj->transform)), \
																local_normal);
	w_normal.w = 0;
	return (normalize(w_normal));
}
