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
	
	color = color_vec.z;
	color += color_vec.y * 256;
	color += color_vec.x * 256 * 256;
	
	return (color);	
}

int	ray_color(float3 vector)
{
    float t;
	int color;
	float3 bottom;
	float3 top;

	bottom = (float3){255.0, 255.0, 255.0};
	top = (float3){0.0, 204.0, 255.0};

	//vector.y should be between 1 and -1
	//1 for top, -1 for bottom
	//wich mean y vector of any ray from camera CANNOT be > 1 or <-1!
	t = 0.5*(vector.y + 1.0);
	//if t = 1 we are at top of screen and 1 - t == 0 (color blue)
	//if t = 0 we are at bottom of screen and t = 0 (color white)
	color = vtoi(t * top);
	// if (t < 0.5)
	// 	color = vtoi(top);
	// else
	// 	color = vtoi(bottom);
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
	int		color;
	float	u;
	float	v;
	
	u = i / (float)WIDTH;
	v = j / (float)HEIGHT;
	
	// creation du vecteur de direction a verifier
	ray_direction = scene.ll_corner + u*scene.width_vec + v*scene.height_vec - scene.origin;
	//normalisation du vecteur?
	// ray_direction = unit_direction(ray_direction);
	color = ray_color(ray_direction);
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
