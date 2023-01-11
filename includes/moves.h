#ifndef MOVES_H
# define MOVES_H

# include "minirt.h"
# include "setup.h"
# include "error.h"

void	change_obj_transform_matr(t_elem *obj);
bool	change_obj_pos(t_elem *obj, int keycode);
void	handle_move(t_scene *scene, int keycode);
void	set_move(t_scene *scene, int x, int y);

#endif