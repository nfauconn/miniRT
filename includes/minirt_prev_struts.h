/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_prev_struts.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/16 12:03:11 by nfauconn         ###   ########.fr       */
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

typedef float			t_float3 __attribute__((ext_vector_type(3)));
typedef float			t_point __attribute__((ext_vector_type(3)));
typedef u_int8_t		t_rgb __attribute__((ext_vector_type(3)));
typedef float			t_vector __attribute__((ext_vector_type(3)));

typedef struct	s_camera				//ONE ONLY
{
	t_point			pos;				//range [-height/2, height/2] [-width/2, width/2]
	t_vector		orientation;		//range [0.0, 1.0]
	float			fov;
}				t_camera;

typedef struct	s_ambiantlight			//ONE ONLY
{
	t_rgb			color;				//range [0, 255]
	float			ratio;				//range [0.0, 1.0]
}				t_ambiantlight;

typedef struct 	s_l						//ONE ONLY (sauf bonus)
{
//	t_rgb			color;		BONUS	//range [0, 255]
	t_point			pos;				//range [-height/2, height/2] [-width/2, width/2]
	float			ratio;				//range [0.0, 1.0]
	struct s_l		*next;
}				t_light;

typedef struct	s_sp
{
	t_rgb			color;				//range [0, 255]
	t_point			pos;				//range [-height/2, height/2] [-width/2, width/2]
	float			diameter;
	float			radius;
	struct s_sp		*next;
}				t_sphere;

typedef struct	s_pl
{
	t_rgb			color;				//range [0, 255]
	t_point			pos;				//range [-height/2, height/2] [-width/2, width/2]
	t_vector		orientation;		//range [-1, 1]
	struct s_pl		*next;
}				t_plan;

typedef struct s_cy
{
	t_rgb			color;				//range [0, 255]
	t_point			pos;				//range [-height/2, height/2] [-width/2, width/2]
	t_vector		orientation;		//range [-1, 1]
	float			diameter;
	float			height;
	struct s_cy		*next;
}				t_cylinder;

typedef struct	s_scene
{
	float			ratio;
	float			height_float;
	float			width_float;
	t_float3			focal_length;
	t_float3			origin;
	t_float3			width_vec;
	t_float3			height_vec;
	t_float3			ll_corner;
	t_element		camera;
	t_element		ambiantlight;
	t_element		*lights;

}				t_scene;

typedef struct	s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}				t_img;

typedef struct s_window
{
	void			*mlx;
	void			*ptr;
	void			**img[2];
	//struct s_mapdata	scene;
}				t_window;

typedef enum e_elements
{
	ambientlight = 0,
	camera,
	lightsource,
	plan,
	sphere,
	cylindre
}	t_elements;

/* ERROR */
t_bool	error_display(char *s);
t_bool	error_display2(char *s1, char *s2);

/* DISPLAY */
int		wincloser(t_window *w);
int		keyparser(int keycode, t_window *w);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* SCENE */
t_scene	setup_scene(char *file);
void	fill_img(t_img img, t_scene scene);
void	display_scene(t_scene scene);

/* VECTOR */
float	dot(t_float3 vector1, t_float3 vector2);

/* SPHERE */
t_bool	hit_sphere(t_float3 center, float radius, t_float3 raydirection, t_scene scene);

#endif
