#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"
# include "ray.h"
# include "lights.h"

float		convert_color_to_unit(float unsigned_c);
float		convert_unit_to_rgb(float unit);
int			rgbvtoi(t_float4 color_vec);
t_rgb		create_color(float red, float green, float blue);
t_rgb		color_at(t_scene *world, t_ray ray);

#endif