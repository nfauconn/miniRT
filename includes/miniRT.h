/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:56:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/30 17:09:32 by nfauconn         ###   ########.fr       */
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

typedef float float3 __attribute__((ext_vector_type(3)));

typedef struct s_window
{
	void				*mlx;
	void				*ptr;
	void				**img[2];
	//struct s_mapdata	scene;
}				t_window;

typedef struct	s_scene
{
	float	ratio;
	float	height_float;
	float	width_float;
	float3	focal_length;
	float3	origin;
	float3	width_vec;
	float3	height_vec;
	float3	ll_corner;
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

void	parse(char *scene);
bool	error_display(char *s);
bool	error_display2(char *s1, char *s2); */
int		wincloser(t_window *w);
int		keyparser(int keycode, t_window *w);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_scene	scene_setup(void);
void	fill_img(t_img img, t_scene scene);

#endif
