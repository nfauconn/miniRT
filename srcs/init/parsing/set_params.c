/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:00:45 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 12:12:21 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

//creer 2 fonctions verif de format (is_coordinates / is_float pour verif
//chaque str de param puis set, et exit clear se charge de free ce qu il faut
//anyway)

int	set_ambiantlight(t_scene *scene, char **params)
{
	if (ft_strarraysize(params) != 3)
		return (error_display("wrong number of elements for ambiant light"));
	if (scene->amblight)
		return (error_display("can be only one ambiant light"));
	scene->amblight = ft_calloc(1, sizeof(t_elem));
	if (!scene->amblight)
		return (error_display("malloc error"));
	if (conv_ratio(params[1], scene->amblight, params[0])
		|| conv_rgb(params[2], scene->amblight, params[0]))
		return (1);
	return (0);
}

void	setup_camera(t_camera *cam, float hsize, float vsize)
{
	float		half_view;
	float		aspect;

	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->transform = identity_matr();
	half_view = tan(cam->fov / 2);
	aspect = cam->hsize / cam->vsize;
	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / cam->hsize;
}

int	set_camera(t_scene *scene, char **params)
{
	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for camera"));
	if (scene->cam)
		return (error_display("can be only one camera"));
	scene->cam = ft_calloc(1, sizeof(t_elem));
	if (!scene->cam)
		return (error_display("malloc error"));
 	if (conv_campos(params[1], scene->cam, params[0])
		|| conv_camorientation(params[2], scene->cam, params[0])
		|| conv_fov(params[3], scene->cam, params[0]))
		return (1);
	scene->cam->fov *= M_PI / 180;
	setup_camera(scene->cam, WIDTH, HEIGHT);
	return (0);
}

/* !!!! no ID cf init_sphere */
int	set_lights(t_scene *scene, char **params)
{
	int		ret;
	t_elem		*newlight;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for light"));
	newlight = ft_calloc(1, sizeof(t_elem));
	if (!newlight)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newlight, params[0])
		|| conv_ratio(params[2], newlight, params[0])
		|| conv_rgb(params[3], newlight, params[0]))
		ret = 1;
	elem_add_back(&scene->lights, newlight);
	return (ret);
}

void	init_sphere(t_elem *s)
{
	static ssize_t	no = -1;

	no++;
	s->id.shape = sphere;
	s->id.no = no;
	s->o_pos = create_point(0, 0, 0);
	s->transform = identity_matr();
	s->material = default_material(s);
}

int	set_sphere(t_scene *scene, char **params)
{
	int		ret;
	t_elem		*newsphere;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for sphere"));
	newsphere = ft_calloc(1, sizeof(t_elem));
	if (!newsphere)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newsphere, params[0])
		|| conv_radius(params[2], newsphere, params[0])
		|| conv_rgb(params[3], newsphere, params[0]))
		ret = 1;
	init_sphere(newsphere);
	elem_add_back(&scene->objs, newsphere);
	return (ret);
}

/* !!!! no ID cf init_sphere */
int	set_plan(t_scene *scene, char **params)
{
	int		ret;
	t_elem		*newplan;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for plan"));
	newplan = ft_calloc(1, sizeof(t_elem));
	if (!newplan)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newplan, params[0])
		|| conv_orientation(params[2], newplan, params[0])
		|| conv_rgb(params[3], newplan, params[0]))
		ret = 1;
	elem_add_back(&scene->objs, newplan);
	return (ret);
}

/* !!!! no ID cf init_sphere */
int	set_cylinder(t_scene *scene, char **params)
{
	int		ret;
	t_elem		*newcylinder;

	if (ft_strarraysize(params) != 6)
		return (error_display("wrong number of elements for cylinder"));
	newcylinder = ft_calloc(1, sizeof(t_elem));
	if (!newcylinder)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newcylinder, params[0])
		|| conv_orientation(params[2], newcylinder, params[0])
		|| conv_diam_height(params[3], params[4], newcylinder, params[0])
		|| conv_rgb(params[5], newcylinder, params[0]))
		ret = 1;
	elem_add_back(&scene->objs, newcylinder);
	return (ret);
}

void	init_paramsetter(t_scene *scene)
{
	scene->fill_params[ambiantlight] = &set_ambiantlight;
 	scene->fill_params[camera] = &set_camera;
	scene->fill_params[lightsource] = &set_lights;
	scene->fill_params[sphere] = &set_sphere;
	scene->fill_params[plan] = &set_plan;
	scene->fill_params[cylinder] = &set_cylinder;
}