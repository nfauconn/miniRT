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
bool	parse_file(char *file, t_scene *scene);
void	init_paramsetter(t_scene *scene);
bool	conv_pos(char *s, t_elem *elem, char *elem_name);
bool	conv_campos(char *s, t_camera *cam, char *elem_name);
bool	conv_orientation(char *s, t_elem *elem, char *elem_name);
bool	conv_camorientation(char *s, t_camera *cam, char *elem_name);
bool	conv_rgb(char *s, t_elem *elem, char *elem_name);
bool	conv_ratio(char *s, t_elem *elem, char *elem_name);
bool	conv_fov(char *s, t_camera *cam, char *elem_name);
bool	conv_radius(char *s, t_elem *elem, char *elem_name);
bool	conv_diam_height(char *s1, char *s2, t_elem *elem, char *elem_name);
void	elem_add_back(t_elem **head, t_elem *to_add);

/* SETTING */
void		init_sphere(t_elem *s);
t_material	default_material(t_elem *elem);
void		setup_camera(t_camera *cam, float hsize, float vsize);

#endif