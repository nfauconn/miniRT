/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene->c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:45:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/07 19:28:44 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->ratio = WIDTH / HEIGHT;
	scene->height_float = 2.0;
	scene->width_float = scene->ratio * scene->height_float;
	scene->focal_length = (float3){0, 0, 1.0};
	scene->origin = (float3){0, 0, 0};
	scene->width_vec = (float3){scene->width_float, 0, 0};
	scene->height_vec = (float3){0, scene->height_float, 0};
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
