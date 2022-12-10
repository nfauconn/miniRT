#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "extern_libs.h"
# include "tuple.h"
# include "matrix.h"
# include "lights.h"
# include "ray.h"
# include "color.h"

typedef	struct	s_camera
{
	float		hsize;
	float		vsize;
	float		fov;
	float		half_width;
	float		half_height;
	float		pixel_size;
	t_m4x4_f	transform;
}				t_camera;

int			nearer_point(t_xs res, t_xs newres);
t_inter		intersect_world(t_scene *world, t_ray ray);
t_inter		prepare_computations(t_inter i, t_ray ray);
t_rgb		shade_hit(t_scene *world, t_inter inter);
t_rgb		color_at(t_scene *world, t_ray ray);
t_m4x4_f	view_transform(t_point from, t_point to, t_point up);
t_camera	setup_camera(float hsize, float vsize, float fov);
t_ray		ray_for_pixel(t_camera cam, float px, float py);
t_rgb		**render(t_camera cam, t_scene world);

#endif