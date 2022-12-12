/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap8_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:39:16 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/12 18:01:12 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"
#include "/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include/criterion/criterion.h"
#include "matrix.h"
#include "minirt.h"
#include "extern_libs.h"
#include "tuple.h"
#include "ray.h"
#include "lights.h"
#include "clang_attr.h"
#include "scene.h"

Test(shadows, yes_no)
{
	//ARRANGE
	t_vector	eyev = create_vector(0, 0, 1);
	t_vector	normalv = create_vector(0, 0, -1);
	t_elem	light;
	point_light(&light, create_point(0, 0, -10), create_color(1, 1, 1));
	bool	in_shadow = 1;
	t_elem sphere;
	init_sphere(&sphere);
	sphere.material.color = create_color(1, 1, 1);
	t_rgb	res = lighting(sphere.material, &light, create_point(0, 0, 0), eyev, normalv, in_shadow);
	cr_expect(same_tuple(res, create_color(0.1, 0.1, 0.1)));
}