/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:19:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/23 12:47:59 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->ratio = WIDTH / HEIGHT;
	scene->height_float = 2.0;
	scene->width_float = scene->ratio * scene->height_float;
	scene->focal_length = (t_float4){0, 0, 1.0, pt};
	scene->origin = (t_float4){0, 0, 0, pt};
	scene->width_vec = (t_float4){scene->width_float, 0, 0, vec};
	scene->height_vec = (t_float4){0, scene->height_float, vec};
	scene->ll_corner = scene->origin - scene->width_vec/2 - scene->height_vec/2 - scene->focal_length;
	init_paramsetter(scene);
}

void	setup_scene(t_scene *scene, char *file)
{
	t_bool	ret;

	init(scene);
	ret = parse_file(file, scene);
	if (ret)
		exit_clear(FAIL, scene);
}
