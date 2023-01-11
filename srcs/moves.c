#include "moves.h"

void	change_obj_transform_matr(t_elem *obj)
{
	if (obj->shape == sphere)
		obj->transform = sp_transform_matr(obj);
	else if (obj->shape == cylinder)
		obj->transform = cyl_transfo_matr(obj);
	else if (obj->shape == plane)
		obj->transform = pl_transform_matr(obj);
}

bool	change_obj_pos(t_elem *obj, int keycode)
{
	if (keycode == UP_ARROW)
		obj->w_pos.y += 0.1;
	else if (keycode == DOWN_ARROW)
		obj->w_pos.y -= 0.1;
	else if (keycode == LEFT_ARROW)
		obj->w_pos.x -= 0.1;
	else if (keycode == RIGHT_ARROW)
		obj->w_pos.x += 0.1;
	else
		return (error_display("not a moving key. please restart\n"));
	return (0);
}

void	handle_move(t_scene *scene, int keycode)
{
	if (change_obj_pos(scene->move.obj, keycode))
		return ;
	change_obj_transform_matr(scene->move.obj);
	printf("drawing...\n");
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
}

void	set_move(t_scene *scene, int x, int y)
{
	t_ray	r;
	t_inter	i;

	scene->move.asked = 1;
	r = ray_for_pixel(*(scene->cam), x, y);
	i = intersect_world(scene, r);
	if (i.t < 0)
		return ;
	scene->move.obj = i.obj;
}