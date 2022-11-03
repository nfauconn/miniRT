/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:56:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/03 15:05:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# define WIDTH 2560
# define HEIGHT 1440

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <errno.h>

typedef double double3 __attribute__((ext_vector_type(3)));

typedef struct s_window
{
	void				*mlx;
	void				*ptr;
	void				**img[2];
	//struct s_mapdata	scene;
}				t_window;

typedef struct	s_scene
{
	double	ratio;
	double	height_double;
	double	width_double;
	double3	focal_length;
	double3	origin;
	double3	width_vec;
	double3	height_vec;
	double3	ll_corner;
}				t_scene;

typedef struct	s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

/* typedef enum e_elements
{
	ambientlight = 0,
	camera,
	lightsource,
	plan,
	sphere,
	cylindre
}	t_elements;

void	parse(char *scene); */

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
double	addition_of_elements_multiplication(double3 vector1, double3 vector2);

/* SPHERE */
bool	hit_sphere(double3 center, double radius, double3 raydirection, t_scene scene);

#endif
