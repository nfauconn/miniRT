#ifndef PARSE_H
# define PARSE_H

# include "extern_libs.h"
# include "defines.h"
# include "structs.h"

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

#endif