/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:10:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/04 20:05:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"
#include "lights.h"

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
	t_point		pos;
	t_rgb		color_sp;
	t_elem		shape;
	t_elem		light;
	t_xs		xs;
	t_inter		xs_hit;
	t_vector	eye;
	t_point		point;
	t_vector	normal;

	init_sphere(&shape);
	shape.material = default_material();
	shape.material.color = create_color(0.2, 0.9, 0);
	light.w_pos = create_point(-10, 10, -10);
	light.color = create_color(1, 1, 1);	y = 0;
	printf("coucou\n");
	while (y < width_pixels)
	{
		world_y = half - pixel_size * y; // compute the world y coordinate (top = +half, bottom = -half)
		x = 0;
		while (x < width_pixels)
		{
			world_x = -half + pixel_size * x;
			pos = (t_point){world_x, world_y, wall_z, pt};
			r = ray(ray_origin, normalize(pos - ray_origin));
			//IS THE RAY NORMALIZED ?????

			shape.transform = shearing((float[6]){1, 0, 0, 0, 0, 0}) * scaling(0.5, 1, 1); //LINE TO TRANFDORM SPHERE
			xs = intersect(shape, r);
			if (xs.count > 0)
			{
				xs_hit = hit(xs);
				if (xs_hit.t >= 0)
				{
					point = position(r, xs_hit.t);
					normal = normal_atsphere(&xs_hit.obj, point);
					eye = -r.dest;
					color_sp = lighting (xs_hit.obj.material, &light, point, eye, normal);

					my_mlx_pixel_put(img, x, y, rgbvtoi(color_sp));
				}
			}
			x++;
		}
		y++;
	}
	printf("finish\n");
}