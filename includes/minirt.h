/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/10 16:06:10 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 300
# define HEIGHT 300
# define BLACK {0, 0, 0, 0}
# define WHITE {1, 1, 1, 0}

# include "extern_libs.h"
# include "structs.h"
# include "ray.h"
# include "matrix.h"
# include "lights.h"
# include "color.h"

/* PARSING */
bool	parse_file(char *file, t_scene *scene);
void	init_paramsetter(t_scene *scene);
bool	conv_pos(char *s, t_elem *elem, char *elem_name);
bool	conv_orientation(char *s, t_elem *elem, char *elem_name);
bool	conv_rgb(char *s, t_elem *elem, char *elem_name);
bool	conv_ratio(char *s, t_elem *elem, char *elem_name);
bool	conv_fov(char *s, t_elem *elem, char *elem_name);
bool	conv_radius(char *s, t_elem *elem, char *elem_name);
bool	conv_diam_height(char *s1, char *s2, t_elem *elem, char *elem_name);
void	elem_add_back(t_elem **head, t_elem *to_add);

/* SCENE */
void	setup_scene(t_scene *scene, char *file);
void	draw_scene(t_img *img);
void	display_scene(t_scene *scene);

/* DISPLAY */
int		close_window(t_scene *scene);
int		parse_key(int keycode, t_scene *scene);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* ERROR */
bool	error_display(char *s);
bool	error_display2(char *s1, char *s2);

/* END */
void	clear(t_scene *scene);
void	exit_clear(bool exit_code, t_scene *scene);

#endif
