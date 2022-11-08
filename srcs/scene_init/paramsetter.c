/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:45 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/08 11:52:02 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//creer 2 fonctions verif de format (is_coordinates / is_float pour verif
//chaque str de param puis set, et exit clear se charge de free ce qu il faut
//anyway)

t_bool	set_rgb(char *s, t_element *elem)
{
	char	**rgb;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (error_display("malloc error"));
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (error_display("wrong rgb value"));
	ft_strarrayclear(rgb);
	return ();
}

t_bool	set_ambiantlight(t_scene *scene, char **params)
{
	float	ratio;
	char	**rgb;

	if (scene->A.specs.ratio >= 0.0)
		return(error_display("can be only one ambiant light"));
	if (!params[1] || !params[2])
		return(error_display("missing elements for ambiant light"));
	if (params[3])
		return(error_display("too many elements for ambiant light"));
	ratio = atof(params[1]); //ecrire un ft atof!!
	if (ratio < 0.0 || ratio > 1.0)
		return(error_display("wrong ratio for ambiant light"));
	scene->A.specs.ratio = ratio;
	return (set_rgb(params[2], &scene->A));
}

t_bool	set_camera(t_scene *scene, char **params)
{

}

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

t_bool	init_paramsetter(t_scene *scene)
{
	scene->fill_params[ambientlight] = &set_ambiantlight;
	scene->fill_params[camera] = &set_camera;
	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[cylinder] = &set_cylinder;
	scene->fill_params[plan] = &set_plan;
}