/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TESTdegradetry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/12 16:56:13 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int vtoi(float3 color_vec)
{
	int	r;
	int	g;
	int	b;

	r = (uint8_t)(color_vec.x);
	g = (uint8_t)(color_vec.y);
	b = (uint8_t)(color_vec.z);
	return (r << 16 | g << 8 | b);
}

int	ray_color(float3 vector, t_scene *scene)
{
    float t;
	int color;
	// float3 bottom = (float3){255.0, 255.0, 255.0};
	float3 top = (float3){0.0, 204.0, 255.0};
	float3	color_red = {255, 0, 0};
	float3 spheres[3] = {{0, 0, -1}, {-1, -1, -1}, 0};

	t = 0.5*(vector.y + 1.0); // vector.y should be between 1 (top) and -1 (bottom)
							//if t = 1 we are at top of screen and (1 - t) == 0 (color blue)
							//if t = 0 we are at bottom of screen and t = 0 (color white)
	if (hit_sphere(spheres[0], 0.5, vector, scene) || hit_sphere(spheres[1], 0.5, vector, scene))
		color = vtoi(color_red);
	else
		color = vtoi(top) * (1 - t);
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