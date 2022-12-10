/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:10:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/10 16:10:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	shape.material.color = create_color(1, 0.9, 0);
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

//			shape.transform = shearing((float[6]){1, 0, 0, 0, 0, 0}) * scaling(0.5, 1, 1); //LINE TO TRANFDORM SPHERE
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