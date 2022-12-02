/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:10:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/02 14:14:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"

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

int rgbvtoi(t_float4 color_vec)
{
	int	r;
	int	g;
	int	b;

	r = convert_float_to_int(color_vec.x);
	g = convert_float_to_int(color_vec.y);
	b = convert_float_to_int(color_vec.z);
	return (r << 16 | g << 8 | b);
}

void	draw_scene(t_img *img)
{
	size_t		x;
	size_t		y;
	float		width_pixels = WIDTH;
	float		wall_size = 7 * width_pixels / 100 ;
	float		pixel_size = wall_size / width_pixels;
	float		half = wall_size / 2;
	float		wall_z = 10; // pos of screen relatively to sphere(0, 0, 0)
	float		world_x;
	float		world_y;
	t_ray		r;
	t_point		ray_origin = {0, 0, -5, pt};
	t_point		position;
	int			color_sp = rgbvtoi((t_vector){1, 0, 0, vec});
	t_elem		shape = init_sphere();
	t_xs		xs;
	t_inter		xs_hit;

	y = 0;
	printf("coucou\n");
	while (y < width_pixels)
	{
		world_y = half - pixel_size * y; // compute the world y coordinate (top = +half, bottom = -half)
		x = 0;
		while (x < width_pixels)
		{
			world_x = -half + pixel_size * x;
			position = (t_point){world_x, world_y, wall_z, pt};
			r = ray(ray_origin, normalize(position - ray_origin));
			shape.transform = shearing((float[6]){1, 0, 0, 0, 0, 0}) * scaling(0.5, 1, 1);
			xs = intersect(shape, r);
			if (xs.count > 0)
			{
				xs_hit = hit(xs);
				if (xs_hit.t >= 0)
				{
//					printf("hit at (%zu, %zu) \n", x, y);
					my_mlx_pixel_put(img, x, y, color_sp);
				}
			}
//			printf("x++\n");
			x++;
		}
//		printf("y++\n");
//		sleep(1);
		y++;
	}
	printf("finish\n");
}