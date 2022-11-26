/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/26 14:15:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 100
# define HEIGHT 100

# include "extern_libs.h"

typedef enum e_elements
{
	ambiantlight = 0,
	camera,
	lightsource,
	plan,
	sphere,
	cylinder,
	elm_nb
}	t_elements;

typedef union u_specs
{
	float				ratio;
	float				radius;
	float				fov;
	float				diam_hght[2];
}	t_specs;

typedef struct s_element
{
	uint8_t				id;
	t_point				pos;
	t_vector			orientation;
	t_rgb				color;
	t_specs				specs;
	struct s_element	*next;
}				t_element;

typedef struct s_img
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}				t_img;

typedef struct s_scene
{
	void			*mlx;
	void			*win;
	t_img			*img;
	float			ratio;
	float			height_float;
	float			width_float;
	t_float4		focal_length;
	t_float4		origin;
	t_float4		width_vec;
	t_float4		height_vec;
	t_float4		ll_corner;
	t_element		*cam;
	t_element		*amblight;
	t_element		*lights;
	t_element		*sp;
	t_element		*cy;
	t_element		*pl;
	bool			(*fill_params[6])(struct s_scene *, char **);
}				t_scene;

/* PARSING */
bool	parse_file(char *file, t_scene *scene);
void	init_paramsetter(t_scene *scene);
bool	conv_pos(char *s, t_element *elem, char *elem_name);
bool	conv_orientation(char *s, t_element *elem, char *elem_name);
bool	conv_rgb(char *s, t_element *elem, char *elem_name);
bool	conv_ratio(char *s, t_element *elem, char *elem_name);
bool	conv_fov(char *s, t_element *elem, char *elem_name);
bool	conv_radius(char *s, t_element *elem, char *elem_name);
bool	conv_diam_height(char *s1, char *s2, t_element *elem, char *elem_name);
void	elem_add_back(t_element **head, t_element *to_add);

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
