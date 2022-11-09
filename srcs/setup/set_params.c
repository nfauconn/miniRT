/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:45 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/09 14:13:59 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//creer 2 fonctions verif de format (is_coordinates / is_float pour verif
//chaque str de param puis set, et exit clear se charge de free ce qu il faut
//anyway)

t_bool	set_rgb(char *s, t_element *elem)
{
	t_bool	ret;
	char	**rgb;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (error_display("malloc error"));
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		ret = error_display("wrong rgb value");
	else
	{
		elem->color.x = atof(rgb[0]);//ecrire ft atof
		elem->color.y = atof(rgb[1]);//same
		elem->color.z = atof(rgb[2]);//same
		if (elem->color.x < 0 || elem->color.x > 255
			|| elem->color.y < 0 || elem->color.y > 255
			|| elem->color.x < 0 || elem->color.z > 255)
			ret = error_display("wrong rgb value");
		else
			ret = 0;
	}
	ft_strarrayclear(&rgb);
	return (ret);
}

t_bool	set_ambiantlight(t_scene *scene, char **params)
{
	t_bool	ret;
	float	ratio;

	if (scene->A)
		return (error_display("can be only one ambiant light"));
	scene->A = malloc(sizeof (t_element));
	if (!scene->A)
		return (error_display("malloc error"));
	ft_bzero(scene->A, sizeof (scene->A));
	if (!params[1] || !params[2])
		return (error_display("missing elements for ambiant light"));
	if (params[3])
		return (error_display("too many elements for ambiant light"));
	ratio = atof(params[1]); //ecrire un ft atof!!
	if (ratio < 0.0 || ratio > 1.0)
		return (error_display("wrong ratio for ambiant light"));
	scene->A->specs.ratio = ratio;
	ret = set_rgb(params[2], scene->A);
	return (ret);
}

/* t_bool	set_camera(t_scene *scene, char **params)
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
 */
void	init_paramsetter(t_scene *scene)
{
	scene->fill_params[ambientlight] = &set_ambiantlight;
/* 	scene->fill_params[camera] = &set_camera;
	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[cylinder] = &set_cylinder;
	scene->fill_params[plan] = &set_plan; */
}