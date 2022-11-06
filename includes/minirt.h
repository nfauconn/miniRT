/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:58:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/06 19:07:12 by nfauconn         ###   ########.fr       */
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

typedef struct	s_element
{
	uint8_t		id;
	t_point			pos;				//								range [-height/2, height/2] [-width/2, width/2]
	t_vector		orientation;		//C + cy						range [0.0, 1.0]
	t_rgb			color;				// A + L + pl + sp + py
	float			ratio;				// A + L
	float			radius;				// sp							(diameter / 2)
	float			height;
	float			fov;
}				t_element;


typedef struct	s_scene
{
	float			ratio;
	float			height_float;
	float			width_float;
	float3			focal_length;
	float3			origin;
	float3			width_vec;
	float3			height_vec;
	float3			ll_corner;
	t_element		C;
	t_element		A;
	t_element		*lights;
	t_element		*sp;
	t_element		*cy;
	t_element		*pl;
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
bool	error_display(char *s);
bool	error_display2(char *s1, char *s2);

/* DISPLAY */
int		wincloser(t_window *w);
int		keyparser(int keycode, t_window *w);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* SCENE */
t_scene	scene_setup(void);
void	fill_img(t_img img, t_scene scene);
void	display_scene(t_scene scene);

/* VECTOR */
float	addition_of_elements_multiplication(float3 vector1, float3 vector2);

/* SPHERE */
bool	hit_sphere(float3 center, float radius, float3 raydirection, t_scene scene);

#endif
