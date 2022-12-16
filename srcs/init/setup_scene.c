/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:19:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 13:46:01 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "setup.h"

static void	init(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->fill_params[ambiantlight] = &set_ambiantlight;
 	scene->fill_params[camera] = &set_camera;
	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[plan] = &set_plan;
	scene->fill_params[cylinder] = &set_cylinder;
}

void	setup_scene(t_scene *scene, char *file)
{
	bool	ret;

	init(scene);
	ret = parse_file(file, scene);
	if (ret)
		exit_clear(FAIL, scene);
}
