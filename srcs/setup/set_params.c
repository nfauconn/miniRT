/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:45 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/09 16:41:28 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//creer 2 fonctions verif de format (is_coordinates / is_float pour verif
//chaque str de param puis set, et exit clear se charge de free ce qu il faut
//anyway)

t_bool	set_ambiantlight(t_scene *scene, char **params)
{
	t_bool	ret;
	float	ratio;

	if (scene->A)
		return (error_display("can be only one ambiant light"));
	scene->A = malloc(sizeof (t_element));
	if (!scene->A)
		return (error_display("malloc error"));
	ft_bzero(scene->A, sizeof (t_element));
	scene->A->next = NULL; //NECESSARY???????
	if (!params[1] || !params[2] || params[3])
		return (error_display("wrong number of elements for ambiant light"));
	ratio = atof(params[1]); //ecrire un ft atof!!
	if (ratio < 0.0 || ratio > 1.0)
		return (error_display("wrong ratio range for ambiant light"));
	scene->A->specs.ratio = ratio;
	ret = convert_rgb(params[2], scene->A);
	return (ret);
}

t_bool	set_camera(t_scene *scene, char **params)
{
	t_bool	ret;
	float	fov;

	if (scene->C)
		return (error_display("can be only one camera"));
	scene->C = malloc(sizeof (t_element));
	if (!scene->C)
		return (error_display("malloc error"));
	ft_bzero(scene->C, sizeof (t_element));
	if (!params[0] || !params[1] || !params[2] || !params[3] || params[4])
		return (error_display("wrong number of elements for camera"));
	ret = convert_pos(params[1], scene->C);
	if (ret)
		return (ret);
	ret = convert_orientation(params[2], scene->C);
	if (ret)
		return (ret);
	fov = atof(params[3]);
	if (fov < 0 || fov > 180)
		return (error_display("wrong fov range for camera"));
	scene->C->specs.fov = fov;
	return (ret);
}
/*
t_bool	set_lights(t_scene *scene, char **params)
{

}

t_bool	set_sphere(t_scene *scene, char **params)
{

}

t_bool	set_plan(t_scene *scene, char **params)
{

}

t_bool	set_cylinder(t_scene *scene, char **params)
{

}
 */
void	init_paramsetter(t_scene *scene)
{
	scene->fill_params[ambientlight] = &set_ambiantlight;
 	scene->fill_params[camera] = &set_camera;
/*	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[cylinder] = &set_cylinder;
	scene->fill_params[plan] = &set_plan; */
}