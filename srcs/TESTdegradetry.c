/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TESTdegradetry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/13 20:29:12 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int vtoi(float3 color_vec)
{
	int	r;
	int	g;
	int	b;

	r = color_vec.x * 255;
	if (color_vec.x * 255 - r >= 0.5)
		r += 1;
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	g = color_vec.y * 255;
	// printf("float left = %f\n", color_vec.y * 255 - g);
	if (color_vec.y * 255 - g >= 0.5)
		g += 1;
	// printf ("g = %d\n", g);
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	b = color_vec.z * 255;
	if (color_vec.z * 255 - b >= 0.5)
		b += 1;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);
}

int	ray_color(float3 vector, t_scene *scene)
{
    float t;
	int color;
	float3 bottom = (float3){1.0, 1.0, 1.0};
	float3 top = (float3){0.5, 0.7, 1.0};
	float3	color_red = {1, 0, 0};
	float3 spheres[3] = {{0, 0, -1}, {-1, -1, -1}, 0};

	t = 0.5*(vector.y + 1.0); // vector.y should be between 1 (top) and -1 (bottom)
							//if t = 1 we are at top of screen and (1 - t) == 0 (color blue)
							//if t = 0 we are at bottom of screen and t = 0 (color white)
	if (hit_sphere(spheres[0], 0.5, vector, scene) || hit_sphere(spheres[1], 0.5, vector, scene))
		color = vtoi(color_red);
	else
	{
		float3 res_color = top * (1.0 - t) + bottom * t;
		color = vtoi(res_color);
	}
	// if (t < 0.5)
	// 	color = vtoi(top);
	// else
	// 	color = vtoi(bottom);
    return (color);
}

int	get_background_color(int i, int j, t_scene *scene)
{
	float3	ray_direction;
	int		color;
	float	u;
	float	v;

	u = i / (float)WIDTH;
	v = j / (float)HEIGHT;

	ray_direction = scene->ll_corner + u*scene->width_vec + v*scene->height_vec - scene->origin;
//	ray_direction = unit_direction(ray_direction); //normalisation du vecteur?
	color = ray_color(ray_direction, scene);
	// if(v > 0.5)
	// 	color = 0xFFFFFF;
	// else
	// 	color = 0x00CCFF;
	return (color);
}

void	draw_scene(t_img *img, t_scene *scene)
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
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}