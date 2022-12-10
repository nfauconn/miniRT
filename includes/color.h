#ifndef COLOR_H
# define COLOR_H

# include "extern_libs.h"

float	convert_color_to_unit(float unsigned_c);
float	convert_unit_to_rgb(float unit);
int		rgbvtoi(t_float4 color_vec);

#endif