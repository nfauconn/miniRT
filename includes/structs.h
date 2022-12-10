/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:24:24 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/10 15:26:03 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "extern_libs.h"

/******************************************************************************/
/*								SCENE										  */
/******************************************************************************/

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

/*******************************************************************************
* 										 RAY								   *
*******************************************************************************/

typedef struct s_ray
{
	t_point		orig;
	t_point		dest;
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
	struct s_inter		*next;
}	t_inter;

#endif