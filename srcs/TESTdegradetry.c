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
	int	r;
	int	g;
	int	b;

	r = (double)(color_vec.x);
	g = (double)(color_vec.y);
	b = (double)(color_vec.z);
	return (r << 16 | g << 8 | b);
}

float	dot(float3 param, float3 param2)
{
	return ((param.x * param2.x) + (param.y * param2.y) + (param.z * param2.z));
}

bool	hit_sphere(float3 center, float radius, float3 raydirection, t_scene scene)
{
	float3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = scene.origin - center;
	a = dot(raydirection, raydirection);
	b = 2.0 * dot(oc, raydirection);
	c = dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

int	ray_color(float3 vector, t_scene scene)
{
    float t;
	int color;
	// float3 bottom = (float3){255.0, 255.0, 255.0};
	float3 top = (float3){0.0, 204.0, 255.0};
	float3	color_red = {255, 0, 0};

	t = 0.5*(vector.y + 1.0); // vector.y should be between 1 (top) and -1 (bottom)
							//if t = 1 we are at top of screen and (1 - t) == 0 (color blue)
							//if t = 0 we are at bottom of screen and t = 0 (color white)
	if (hit_sphere((float3){0, 0, 1}, 0.5, vector, scene))
		color = vtoi(color_red) * (1 - t);
	else
		color = vtoi(top) * (1 - t);
	// if (t < 0.5)
	// 	color = vtoi(top);
	// else
	// 	color = vtoi(bottom);
    return (color);
}

float length_squared(float3 vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
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
	int		color;
	float	u;
	float	v;

	u = i / (float)WIDTH;
	v = j / (float)HEIGHT;

	ray_direction = scene.ll_corner + u*scene.width_vec + v*scene.height_vec - scene.origin;
	ray_direction = unit_direction(ray_direction); //normalisation du vecteur?
	color = ray_color(ray_direction, scene);
	// if(v > 0.5)
	// 	color = 0xFFFFFF;
	// else
	// 	color = 0x00CCFF;
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
