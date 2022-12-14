#ifndef DISPLAY_H
# define DISPLAY_H

# include "extern_libs.h"
# include "defines.h"
# include "structs.h"
# include "scene.h"
# include "error.h"
# include "exit.h"

int		close_window(t_scene *scene);
int		parse_key(int keycode, t_scene *scene);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	display_scene(t_scene *scene);

#endif