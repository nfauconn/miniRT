#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "extern_libs.h"
# include "tuple.h"
# include "matrix.h"
# include "lights.h"
# include "ray.h"
# include "color.h"

int			nearer_point(t_xs res, t_xs newres);
t_inter		intersect_world(t_scene *world, t_ray ray);
void		prepare_computations(t_inter *i, t_ray ray);
t_rgb		shade_hit(t_scene *world, t_inter inter);
t_rgb		color_at(t_scene *world, t_ray ray);
t_m4x4_f	view_transform(t_point from, t_point to, t_point up);
void		setup_camera(t_camera *cam, float hsize, float vsize);
t_ray		ray_for_pixel(t_camera cam, float px, float py);
void		render(t_scene *scene, t_img *img);

#endif