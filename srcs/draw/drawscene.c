/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:10:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/17 18:56:24 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	drawscene(t_scene *scene, t_img *img)
{
/* 	t_elem	*middle = scene->objs;
//	float	rM = middle->specs.ratio;
	middle->transform = translation(-0.5, 1, 0.5);

	t_elem	*right = middle->next;
//	right->transform = matrix_mult(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	// float	rR = right->specs.ratio;
	right->transform = matrix_mult(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));

	t_elem	*left = right->next;
	// float	rL = left->specs.ratio;
	left->transform = matrix_mult(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)); */

	/* t_elem	*pl = left->next;
	pl->transform = matrix_mult(pl->transform, translation(0, 0, 3));
//	pl->transform = matrix_mult(pl->transform, rotation_x(M_PI / 2)); */

	scene->cam->transform = view_transform(create_point(0, 1, -5), \
												create_point(0, 1, 0), \
												create_vector(0, 1, 0));

	render(scene, img);
}
/*

3 SPHERES MODIFIED TO BE PLANES

	t_elem	*floor = left->next;
	floor->material.specular = 0;
	floor->transform = scaling(10.0, 0.01, 10);

	t_elem	*left_wall = floor->next;
	left_wall->transform = matrix_mult(translation(0, 0, 5), rotation_y(-M_PI / 4));
	left_wall->transform = matrix_mult(left_wall->transform, rotation_x(M_PI / 2));
	left_wall->transform = matrix_mult(left_wall->transform, scaling(10.0, 0.01, 10));
	left_wall->material.specular = 0;
	t_elem	*right_wall = left_wall->next;
	right_wall->transform = matrix_mult(translation(0, 0, 5), rotation_y(M_PI / 4));
	right_wall->transform = matrix_mult(right_wall->transform, rotation_x(M_PI / 2));
	right_wall->transform = matrix_mult(right_wall->transform, scaling(10.0, 0.01, 10));
	right_wall->material.specular = 0;

 
*/