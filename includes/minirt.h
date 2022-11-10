/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/10 14:40:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 2560
# define HEIGHT 1440

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <errno.h>
# include <sys/types.h>
# include <stdint.h>

typedef float			float3 __attribute__((ext_vector_type(3)));
typedef float			t_point __attribute__((ext_vector_type(3)));
typedef uint8_t			t_rgb __attribute__((ext_vector_type(3)));
typedef float			t_vector __attribute__((ext_vector_type(3)));

typedef enum e_elements
{
	ambientlight = 0,
	camera,
	lightsource,
	plan,
	sphere,
	cylinder,
	elements_nb
}	t_elements;

typedef union	u_specs
{
	float				ratio;
	float				radius;
	float				fov;
	float				diam_hght[2];
}	t_specs;

typedef struct	s_element
{
	uint8_t				id;
	t_point				pos;
	t_vector			orientation;
	t_rgb				color;
	t_specs				specs;
	struct s_element	*next;
}				t_element;

typedef struct	s_img
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}				t_img;

typedef struct	s_scene
{
	void				*mlx;
	void				*win;
	t_img				*img;
	float				ratio;
	float				height_float;
	float				width_float;
	float3				focal_length;
	float3				origin;
	float3				width_vec;
	float3				height_vec;
	float3				ll_corner;
	t_element			*C;
	t_element			*A;
	t_element			*L;
	t_element			*sp;
	t_element			*cy;
	t_element			*pl;
	t_bool				(*fill_params[elements_nb])(struct s_scene *, char **);
}				t_scene;

/* ERROR */
t_bool	error_display(char *s);
t_bool	error_display2(char *s1, char *s2);

/* END */
void	clear(t_scene *scene);
void	exit_clear(t_bool exit_code, t_scene *scene);

/* PARSING */
t_bool	parse_file(char *file, t_scene *scene);
void	init_paramsetter(t_scene *scene);
t_bool	conv_pos(char *s, t_element *elem, char *elem_name);
t_bool	conv_orientation(char *s, t_element *elem, char *elem_name);
t_bool	conv_rgb(char *s, t_element *elem, char *elem_name);
t_bool	conv_ratio(char *s, t_element *elem, char *elem_name);
t_bool	conv_fov(char *s, t_element *elem, char *elem_name);
t_bool	conv_radius(char *s, t_element *elem, char *elem_name);
t_bool	conv_diam_height(char *s1, char *s2, t_element *elem, char *elem_name);
void	elem_add_back(t_element **head, t_element *to_add);

/* DISPLAY */
int		close_window(t_scene *scene);
int		parse_key(int keycode, t_scene *scene);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* SCENE */
void	setup_scene(t_scene *scene, char *file);
void	draw_scene(t_img *img, t_scene *scene);
void	display_scene(t_scene *scene);

/* VECTOR */
float	addition_of_elements_multiplication(float3 vector1, float3 vector2);

/* SPHERE */
t_bool	hit_sphere(float3 center, float radius, float3 raydirection, t_scene *scene);

#endif
