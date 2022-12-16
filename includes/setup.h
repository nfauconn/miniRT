#ifndef SETUP_H
# define SETUP_H

# include "minirt.h"
# include "tuple.h"
# include "matrix.h"
# include "exit.h"
# include "error.h"
# include "color.h"

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

/* CAMERA */
int			set_camera(t_scene *scene, char **params);
void		init_camera(t_camera *cam, float hsize, float vsize);

/* CYLINDER */
int			set_cylinder(t_scene *scene, char **params);

/* LIGHTSOURCE */
int			set_lights(t_scene *scene, char **params);

/* PLAN */
int			set_plan(t_scene *scene, char **params);

/* MATERIAL */
t_material	default_material(t_elem *elem);

#endif