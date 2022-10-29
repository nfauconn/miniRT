/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/27 21:14:12 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"
#include <stdio.h>
// #include "libft/includes/libft.h"
// #include "mlx/mlx.h"

typedef float float3 __attribute__((ext_vector_type(3)));

typedef struct s_libwin
{
	void				*mlx;
	void				*win;
	void				**img[2];
	//struct s_mapdata	scene;
}				t_libwin;

typedef struct	s_graphic
{
	float	ratio;
	float	view_heigth;
	float	view_width;
	float3	focal_length;
	float3	origin;
	float3	horizontal;
	float3	vertical;
	float3	ll_corner;
}				t_graphic;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	wincloser(t_libwin *libwin)
{
	size_t	i;

	i = 0;
	while (i < 1)//need check if img exist
	{
		if (libwin->img[i])
		{
			mlx_destroy_image(libwin->mlx, libwin->img[i]);
		}
		i++;
	}
	if (libwin->win)
		mlx_destroy_window(libwin->mlx, libwin->win);
	mlx_destroy_display(libwin->mlx);
	free(libwin->mlx);
	exit(0);
}

int	keyparser(int keycode, t_libwin *libwin)
{
	if (keycode == 65307)
		wincloser(libwin);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int vtoi(float3 vcolor)
{
	int color;
	
	color = vcolor.z * 255;
	color += vcolor.y * 255 * 100;
	color += vcolor.x * 255 * 10000;
	
	return (color);	
}

int	ray_color(float3 vector)
{
    float t;
	int color;
	float3 bottom;
	float3 top;

	bottom = (float3){1.0, 1.0, 1.0};
	top = (float3){0.5, 0.7, 1.0};

	t = 0.5*(vector.y + 1.0);
	printf ("vector x, y and z are %f, %f and %f \n", vector.x, vector.y, vector.z);
	printf ("t = %f\n", t);
	color = vtoi(((1.0 - t) * bottom) + (t * top));
	printf ("color = %d\n", color);
    return (color);
}

float length_squared(float3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float calcul_length(float3 vector)
{
	float res;

	res = sqrt(length_squared(vector));
	return (res);
}

float3	unit_direction(float3 vector)
{
	float	length;
	float3	res;
	
	length = calcul_length(vector);
	res = vector / length;
	return (res);
}

int	get_background_color(int i, int j, t_graphic graph)
{
	// float3	ray_direction;
	float	u;
	float	v;
	(void)graph;
	
	u = i / (float)WIDTH - 1;
	v = j / (float)HEIGHT - 1;
	
	printf ("u and v are %f and %f\n", u, v);
	// ray_direction = graph.ll_corner + u*graph.horizontal + v*graph.vertical - graph.origin;
	// printf ("ray_direction y = %f\n", ray_direction.y);
	// ray_direction = unit_direction(ray_direction);
	//here need unit_direction from ray_direction....
	int	color = ray_color(v);
	return (color);
}

void	fill_img(t_data data, t_graphic graph)
{
	int	color;
	int	i;
	int	j;
	
	i = 0;
	while (i <= 500)
	{
		j = 0;
		while (j <= HEIGHT)
		{
			color = get_background_color(i, j, graph);
			my_mlx_pixel_put(&data, i, j, color);
			j++;
		}
		printf ("end of colon\n");
		i++;
	}
}

t_graphic	graph_setup(void)
{
	t_graphic	res;
	float width;
	float height;

	width = WIDTH;
	height = HEIGHT;
	
	res.ratio = width / height;
	printf ("ratio = %f\n", res.ratio);
	res.view_heigth = 2.0;
	res.view_width = res.ratio * res.view_heigth;
	res.focal_length = (float3){0, 0, 1.0};
	printf ("focal length x, y and z are %f, %f and %f \n", res.focal_length.x, res.focal_length.y, res.focal_length.z);
	res.origin = (float3){0, 0, 0};
	printf ("origin x, y and z are %f, %f and %f \n", res.origin.x, res.origin.y, res.origin.z);
	res.horizontal = (float3){res.view_width, 0, 0};
	printf ("horzontal x, y and z are %f, %f and %f \n", res.horizontal.x, res.horizontal.y, res.horizontal.z);
	res.vertical = (float3){0, res.view_heigth, 0};
	printf ("vertical x, y and z are %f, %f and %f \n", res.vertical.x, res.vertical.y, res.vertical.z);
	res.ll_corner = res.origin - res.horizontal/2 - res.vertical/2 - res.focal_length;
	return (res);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_libwin	libwin;
	t_data	img;
	t_graphic graph;

	libwin.mlx = mlx_init();
	libwin.win = mlx_new_window(libwin.mlx, WIDTH, HEIGHT, "MiniRT");
	img.img = mlx_new_image(libwin.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	graph = graph_setup();
	fill_img (img, graph);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	libwin.img[0] = img.img;
	/*function need mlx instance, windows, img, position start*/
	mlx_put_image_to_window(libwin.mlx, libwin.win, libwin.img[0], 0, 0);
	mlx_hook(libwin.win, 2, 1L << 0, keyparser, &libwin);
	mlx_hook(libwin.win, 17, 1L << 2, wincloser, &libwin);
	mlx_loop(libwin.mlx);
}

