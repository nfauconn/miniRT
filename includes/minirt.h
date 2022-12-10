/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/10 14:05:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 300
# define HEIGHT 300
# define BLACK {0, 0, 0, 0}
# define WHITE {1, 1, 1, 0}

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
}	t_elems;

typedef union u_specs
{
	float				ratio;
	float				radius;
	float				fov;
	float				diam_hght[2];
}	t_specs;

typedef struct s_id
{
	uint8_t	shape;
	size_t	no;
}	t_id;

typedef struct s_material
{
	t_rgb	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

typedef struct s_elem
{
	t_id				id;
	t_point				o_pos;
	t_point				w_pos;
	t_vector			orientation;
	t_rgb				color;
	t_m4x4_f			transform;
	t_material			material; /* A INIT DANS LE PARSING*/
	t_specs				specs;
	struct s_elem		*next;
}				t_elem;

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
	t_elem			*cam;
	t_elem			*amblight;
	t_elem			*lights;
	t_elem			*objs;
	int				(*fill_params[6])(struct s_scene *, char **);
}				t_scene;

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
