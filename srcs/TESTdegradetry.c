/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degradetry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/30 17:04:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int vtoi(float3 color_vec)
{
	int color;
	
	color = color_vec.z * 255;
	color += color_vec.y * 255 * 100;
	color += color_vec.x * 255 * 10000;
	
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
	color = vtoi(((1.0 - t) * bottom) + (t * top));
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

int	get_background_color(int i, int j, t_scene scene)
{
	float3	ray_direction;
	float	u;
	float	v;
	
	u = i / (float)WIDTH;
	v = j / (float)HEIGHT;
	
	ray_direction = scene.ll_corner + u*scene.width_vec + v*scene.height_vec - scene.origin;
	ray_direction = unit_direction(ray_direction);
	int	color = ray_color(ray_direction);
	return (color);
}

void	fill_img(t_img img, t_scene scene)
{
	int	color;
	int	i;
	int	j;
	
	i = 0;
	while (i <= WIDTH)
	{
		j = 0;
		while (j <= HEIGHT)
		{
			color = get_background_color(i, j, scene);
			my_mlx_pixel_put(&img, i, j, color);
			j++;
		}
		i++;
	}
}

t_scene	scene_setup(void)
{
	t_scene		res;
	float		width;
	float		height;

	width = WIDTH;
	height = HEIGHT;
	
	res.ratio = width / height;
	res.height_float = 2.0;
	res.width_float = res.ratio * res.height_float;
	res.focal_length = (float3){0, 0, 1.0};
	res.origin = (float3){0, 0, 0};
	res.width_vec = (float3){res.width_float, 0, 0};
	res.height_vec = (float3){0, res.height_float, 0};
	res.ll_corner = res.origin - res.width_vec/2 - res.height_vec/2 - res.focal_length;
	return (res);
}
