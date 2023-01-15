/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:04:15 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/15 21:00:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_m4x4_f	view_transform(t_point from, t_point to, t_vector up)
{
	t_m4x4_f	res;
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_up;

	to = create_vector(to.x, to.y, to.z);
	forward = normalize(to);
	upn = normalize(up);
	left = normalize(cross_product(forward, upn));
	true_up = normalize(cross_product(left, forward));
	res = identity_matr();
	res[0][0] = left.x;
	res[0][1] = left.y;
	res[0][2] = left.z;
	res[1][0] = true_up.x;
	res[1][1] = true_up.y;
	res[1][2] = true_up.z;
	res[2][0] = -forward.x;
	res[2][1] = -forward.y;
	res[2][2] = -forward.z;
	return (matrix_mult(res, translation(-from.x, -from.y, -from.z)));
}

t_ray	ray_for_pixel(t_camera cam, float px, float py)
{
	float		world_x;
	float		world_y;
	t_ray		res;
	t_float4	pixel;

	world_x = cam.half_width - ((px + 0.5) * cam.pixel_size);
	world_y = cam.half_height - ((py + 0.5) * cam.pixel_size);
	pixel = matrix_tuple_mult(inverse(cam.transform),
			create_point(world_x, world_y, -1));
	res.orig = matrix_tuple_mult(inverse(cam.transform), create_point(0, 0, 0));
	res.dir = normalize(pixel - res.orig);
	return (res);
}
