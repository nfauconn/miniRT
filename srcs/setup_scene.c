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

// NE PAS OUBLIER :
//	- verif que les 3 elements uniques sont contenus 1 seule fois

t_scene	*setup_scene(char *file)
{
	t_scene		*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit (error_display("malloc error"));
	init(scene);
	parse(file, scene);
	return (scene);
}
