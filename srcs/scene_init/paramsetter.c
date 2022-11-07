/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:45 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/07 23:03:32 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//creer 2 fonctions verif de format (is_coordinates / is_float pour verif
//chaque str de param puis set, et exit clear se charge de free ce qu il faut
//anyway)

void	set_ambiantlight(t_scene *scene, char **params)
{

}

void	set_camera(t_scene *scene, char **params)
{

}

void	set_lights(t_scene *scene, char **params)
{

}

void	set_sphere(t_scene *scene, char **params)
{

}

void	set_plan(t_scene *scene, char **params)
{

}

void	set_cylinder(t_scene *scene, char **params)
{

}

void	init_paramsetter(t_scene *scene)
{
	scene->fill_params[ambientlight] = &set_ambiantlight;
	scene->fill_params[camera] = &set_camera;
	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[cylinder] = &set_cylinder;
	scene->fill_params[plan] = &set_plan;
}