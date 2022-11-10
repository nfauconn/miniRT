/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:45 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/10 14:43:05 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//creer 2 fonctions verif de format (is_coordinates / is_float pour verif
//chaque str de param puis set, et exit clear se charge de free ce qu il faut
//anyway)

t_bool	set_ambiantlight(t_scene *scene, char **params)
{
	if (ft_strarraysize(params) != 3)
		return (error_display("wrong number of elements for ambiant light"));
	if (scene->A)
		return (error_display("can be only one ambiant light"));
	scene->A = ft_calloc(1, sizeof(t_element));
	if (!scene->A)
		return (error_display("malloc error"));
	if (conv_ratio(params[1], scene->A, params[0])
		|| conv_rgb(params[2], scene->A, params[0]))
		return (1);
	return (0);
}

t_bool	set_camera(t_scene *scene, char **params)
{
	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for camera"));
	if (scene->C)
		return (error_display("can be only one camera"));
	scene->C = ft_calloc(1, sizeof(t_element));
	if (!scene->C)
		return (error_display("malloc error"));
	if (conv_pos(params[1], scene->C, params[0])
		|| conv_orientation(params[2], scene->C, params[0])
		|| conv_fov(params[3], scene->C, params[0]))
		return (1);
	return (0);
}

t_bool	set_lights(t_scene *scene, char **params)
{
	t_element	*newlight;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for light"));
	newlight = ft_calloc(1, sizeof(t_element));
	if (!newlight)
		return (error_display("malloc error"));
	if (conv_pos(params[1], newlight, params[0])
		|| conv_ratio(params[2], newlight, params[0])
		|| conv_rgb(params[3], newlight, params[0]))
		return (1);
	elem_add_back(&scene->L, newlight);
	return (0);
}

t_bool	set_sphere(t_scene *scene, char **params)
{
	t_element	*newsphere;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for sphere"));
	newsphere = ft_calloc(1, sizeof(t_element));
	if (!newsphere)
		return (error_display("malloc error"));
	if (conv_pos(params[1], newsphere, params[0])
		|| conv_radius(params[2], newsphere, params[0])
		|| conv_rgb(params[3], newsphere, params[0]))
		return (1);
	elem_add_back(&scene->sp, newsphere);
	return (0);
}

t_bool	set_plan(t_scene *scene, char **params)
{
	t_element	*newplan;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for plan"));
	newplan = ft_calloc(1, sizeof(t_element));
	if (!newplan)
		return (error_display("malloc error"));
	if (conv_pos(params[1], newplan, params[0])
		|| conv_orientation(params[2], newplan, params[0])
		|| conv_rgb(params[3], newplan, params[0]))
		return (1);
	elem_add_back(&scene->pl, newplan);
	return (0);
}

t_bool	set_cylinder(t_scene *scene, char **params)
{
	t_element	*newcylinder;

	if (ft_strarraysize(params) != 6)
		return (error_display("wrong number of elements for cylinder"));
	newcylinder = ft_calloc(1, sizeof(t_element));
	if (!newcylinder)
		return (error_display("malloc error"));
	if (conv_pos(params[1], newcylinder, params[0])
		|| conv_orientation(params[2], newcylinder, params[0])
		|| conv_diam_height(params[3], params[4], newcylinder, params[0])
		|| conv_rgb(params[5], newcylinder, params[0]))
		return (1);
	elem_add_back(&scene->cy, newcylinder);
	return (0);
}

void	init_paramsetter(t_scene *scene)
{
	scene->fill_params[ambientlight] = &set_ambiantlight;
 	scene->fill_params[camera] = &set_camera;
	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[plan] = &set_plan;
	scene->fill_params[cylinder] = &set_cylinder;
}