/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:04:15 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/07 19:39:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	nearer_point(t_xs res, t_xs newres)
{
	if(newres.t[0] >= 0)
	{
		if(newres.t[0] < res.t[0] && newres.t[0] < res.t[1])
		return (1);
	}
	if(newres.t[1] >= 0)
	{
		if(newres.t[1] < res.t[0] && newres.t[1] < res.t[1])
		return (1);
	}
	return (0);
}

/* find hits of objects */
t_inter	intersect_world(t_scene *world, t_ray ray)
{
	t_elem		obj;
	t_xs		xs;
	t_inter		i;
	t_inter		res;

	obj = world->objs;
	xs = intersect(obj, ray);
	i = hit(xs);
	res = i;
	while (obj)
	{
		xs = intersect(obj, ray);
		i = hit(xs);
		if (i.t > 0 && i.t < res.t)
			res = i;
		obj = obj->next;
	}
}

/* t_xs	intersect_world(t_scene *world, t_ray ray) //t_inter *intersect_world ??? like list of t_inter with every shapes
{
	t_elem	*shape;
	t_xs	res;
	// t_xs	new_res;

	shape = world->objs;
	res = intersect(*shape, ray);
	printf("%f\n", res.t[0]);
	printf("%f\n", res.t[1]);
	// while (shape.next != NULL)
	// {
	// 	new_res = intersect(shape, ray);
	// 	if (nearer_point(res, new_res))
	// 		res = new_res;
	// 	shape = *shape.next;
	// }
	// if (res.t[1] >= 0 && res.t[1] < res.t[0])
	// 	res.t[0] = res.t[1];
	return (res);
} */

t_comps	prepare_computations(t_inter i, t_ray ray)
{
	t_comps	compres;

	compres.t = i.t;
	compres.obj = i.obj;
	compres.point = position(ray, compres.t);
	compres.eyev = -ray.dest;
	compres.normalv = normal_atsphere(&compres.obj, compres.point);
	if (dot_product(compres.normalv, compres.eyev) < 0)
	{
		compres.inside = 1;
		compres.normalv = -compres.normalv;
	}
	else
		compres.inside = 0;
	return(compres);
}

/*
to support multiple light sources : iterate over all the light sources,
calling lighting() for each one and adding the colors together
"Be warned, though: adding multiple light sources will slow your renderer down,
especially when you get to Chapter 8, Shadows, on page 109. But if you have CPU
cycles to burn, having more than one light can make some neat effects possible, like
overlapping shadows"
*/
t_rgb	shade_hit(t_scene *world, t_comps comps)
{
	return (lighting(comps.obj.material, world->lights, comps.point, comps.eyev, comps.normalv));
}

/* intersect the world with the given ray and return the color at the given intersection */
t_rgb	color_at(t_scene *world, t_ray ray)
{

}

t_m4x4_f	view_transform(t_point from, t_point to, t_point up)
{
	t_m4x4_f	res;
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_up;

	forward = normalize(to - from);
	upn = normalize(up);
	left = cross_product(forward, upn);
	true_up = cross_product(left, forward);
	res = identity_matr();
	res[0][0] = left.x;
	res[0][1] = left.y;
	res[0][2] = left.z;
	res[1][0] = true_up.x;
	res[1][1] = true_up.y;
	res[1][2] = true_up.z;
	res[2][0] = -forward.x;
	res[2][1] = -forward.y;
	res[2][2] = -forward.z;
	return (matrix_mult(res, translation(-from.x, -from.y, -from.z)));
}

//aspect is the aspect ratio, like 16:9
t_camera	setup_camera(float hsize, float vsize, float fov)
{
	t_camera	cam;
	float		half_view;
	float		aspect;

	cam.hsize = hsize;
	cam.vsize = vsize;
	cam.fov = fov;
	cam.transform = identity_matr();
	half_view = tan(fov / 2);
	aspect = cam.hsize / cam.vsize;
	if (aspect >= 1)
	{
		cam.half_width = half_view;
		cam.half_height = half_view / aspect;
	}
	else
	{
		cam.half_width = half_view * aspect;
		cam.half_height = half_view;
	}
	cam.pixel_size = (cam.half_width * 2) / cam.hsize;
	return (cam);
}

t_ray	ray_for_pixel(t_camera cam, float px, float py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;

	x_offset = (px + 0.5) * cam.pixel_size;
	y_offset = (py + 0.5) * cam.pixel_size;
	world_x = cam.half_width - x_offset;
	world_y = cam.half_height - y_offset;

	t_ray	res;
	t_float4	pixel;
	pixel = matrix_tuple_mult(inverse(cam.transform), create_point(world_x, world_y, -1));
	res.orig = matrix_tuple_mult(inverse(cam.transform), create_point(0, 0, 0));
	res.dest = normalize(pixel - res.orig);
	return (res);
}

//t_rgb ** as return type is probably a bad idea
//because it would need to malloc a biiig amount of memory
//but it would work as an idea and produce a tab of color, pixel by pixel
/* t_rgb	**render(t_camera cam, t_scene world)
{
	int		x;
	int		y;
	t_ray	ray;
	t_rgb	color;
	t_rgb	**image;
	//image could be the mlx image in th final version
	//canvas doesn't even exist yet, it should be a kind of big malloc, i guess
	image = (cam.hsize, cam.vsize);
	//it write color in the image, line by line, column by column
	//depending from what the new ray touch in the world
	y = 0;
	while(y < cam.vsize - 1)
	{
		x = 0;
		while (x < cam.hsize - 1)
		{
			ray = ray_for_pixel(cam, x, y);
			color = color_at(world, ray);
			//this should be replaced by my_mlx_pixelput
			image[y][x] = color;
			x++;
		}
		y++;
	}
	return (image);
}
 */