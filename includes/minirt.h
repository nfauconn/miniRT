/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 18:44:50 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "externlibs.h"

typedef float __attribute__((ext_vector_type(4)))	t_float4;
typedef t_float4									t_point;
typedef t_float4									t_vector;
typedef t_float4									t_rgb;
typedef int __attribute__((ext_vector_type(4)))		t_int4;
typedef float __attribute__((matrix_type(4, 4)))	t_m4x4_f;
typedef t_m4x4_f									t_m3x3_f;
typedef int __attribute__((matrix_type(4, 4)))		t_m4x4_i;

# define WIDTH 300
# define HEIGHT 150
# define BLACK {0, 0, 0, 0}
# define WHITE {1, 1, 1, 0}
# define EPSILON 0.0001

/******************************************************************************/
/*								SCENE										  */
/******************************************************************************/

typedef enum e_elements
{
	ambiantlight = 0,
	camera,
	lightsource,
	plane,
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
	t_id			id;
	t_point			o_pos;
	t_point			w_pos;
	t_vector		orientation;
	t_rgb			color;
	t_m4x4_f		transform;
	t_material		material; /* A INIT DANS LE PARSING*/
	t_specs			specs;
	struct s_elem	*next;
}				t_elem;

typedef	struct	s_camera //attention !! position et orientation cam a mettre dans le parsing ?
{
	float			fov;
	t_point			o_pos;
	t_point			w_pos;
	t_vector		orientation;
	t_m4x4_f		transform;
	float			hsize;
	float			vsize;
	float			half_height;
	float			half_width;
	float			pixel_size;
}				t_camera;

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
	t_camera		*cam;
	t_elem			*amblight;
	t_elem			*lights;
	t_elem			*objs;
	int				(*fill_params[6])(struct s_scene *, char **);
}				t_scene;

/*******************************************************************************
* 										 RAY								   *
*******************************************************************************/

typedef struct s_ray
{
	t_point		orig;
	t_point		dir;
}	t_ray;

typedef struct s_xs
{
	size_t		count;
	float		t[2];
	t_elem		obj;
}	t_xs;

typedef struct s_inter
{
	float				t;
	t_elem				obj;
	t_point				point;
	t_vector			eyev;
	t_vector			normalv;
	bool				inside;
	t_point				over_point;
	struct s_inter		*next;
}	t_inter;

#endif
