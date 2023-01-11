/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:18:36 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/11 15:02:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "minirt.h"
# include "tuple.h"
# include "matrix.h"
# include "exit.h"
# include "error.h"
# include "scene.h"
# include "rgb.h"

void	setup_scene(t_scene *scene, char *file);

/* PARSING */
bool		parse_file(char *file, t_scene *scene);
bool		conv_pos(char *s, t_elem *elem, char *elem_name);
bool		conv_campos(char *s, t_camera *cam, char *elem_name);
bool		conv_orientation(char *s, t_elem *elem, char *elem_name);
bool		conv_camorientation(char *s, t_camera *cam, char *elem_name);
bool		conv_rgb(char *s, t_elem *elem, char *elem_name);
bool		conv_ratio(char *s, t_elem *elem, char *elem_name);
bool		conv_fov(char *s, t_camera *cam, char *elem_name);
bool		conv_radius(char *s, t_elem *elem, char *elem_name);
bool		conv_diam_height(char *s1, char *s2, t_elem *elem, char *elem_name);
void		elem_add_back(t_elem **head, t_elem *to_add);

/* AMBLIGHT */
int			set_ambiantlight(t_scene *scene, char **params);

/* SPHERE */
int			set_sphere(t_scene *scene, char **params);
void		init_sphere(t_elem *s);
t_m4x4_f	sp_transform_matr(t_elem *s);

/* CAMERA */
int			set_camera(t_scene *scene, char **params);
void		init_camera(t_camera *cam, float hsize, float vsize);

/* CYLINDER */
int			set_cylinder(t_scene *scene, char **params);
t_m4x4_f	cyl_transfo_matr(t_elem *cyl);

/* LIGHTSOURCE */
int			set_lights(t_scene *scene, char **params);

/* plane */
int			set_plane(t_scene *scene, char **params);
void		init_plane(t_elem *pl);
t_m4x4_f	pl_transform_matr(t_elem *pl);

/* MATERIAL */
t_material	default_material(t_elem *elem);

#endif