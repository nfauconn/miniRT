#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"
# include "ray.h"
# include "lights.h"

t_rgb		create_color(float red, float green, float blue);
t_rgb		color_at(t_scene *world, t_ray ray);

#endif