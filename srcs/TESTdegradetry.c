/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TESTdegradetry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/16 13:15:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	convert_float_to_int(float hexa)
{
	int	res;

	res = hexa * 255;
	if (hexa * 255 - res >= 0.5)
		res += 1;
	if (res > 255)
		res = 255;
	if (res < 0)
		res = 0;
	return (res);
}

int rgbvtoi(t_float3 color_vec)
{
	int	r;
	int	g;
	int	b;

	r = convert_float_to_int(color_vec.x);
	g = convert_float_to_int(color_vec.y);
	b = convert_float_to_int(color_vec.z);
	return (r << 16 | g << 8 | b);
}

int	ray_color(t_float3 vector, t_scene *scene)
{
    float t;
	int color;
	t_float3 bottom = (t_float3){1.0, 1.0, 1.0};
	t_float3 top = (t_float3){0.5, 0.7, 1.0};
	t_float3	color_red = {1, 0, 0};
	t_float3 spheres[3] = {{0, 0, -1}, {-1, -1, -1}, 0};

	t = 0.5*(vector.y + 1.0); // vector.y should be between 1 (top) and -1 (bottom)
							//if t = 1 we are at top of screen and (1 - t) == 0 (color blue)
							//if t = 0 we are at bottom of screen and t = 0 (color white)
	if (hit_sphere(spheres[0], 0.5, vector, scene) || hit_sphere(spheres[1], 0.5, vector, scene))
		color = rgbvtoi(color_red);
	else
	{
		t_float3 res_color = top * (1.0 - t) + bottom * t;
		color = rgbvtoi(res_color);
	}
    return (color);
}

int	get_background_color(int i, int j, t_scene *scene)
{
	t_float3	ray_direction;
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