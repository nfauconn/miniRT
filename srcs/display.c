#include "display.h"
#include "ray.h"
#include "inter.h"

int	close_window(t_scene *scene)
{
	if (scene->img->ptr)
		mlx_destroy_image(scene->mlx, scene->img->ptr);
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	exit_clear(0, scene);
	return(0);
}

/* static int	render_next_frame(t_scene *scene)
{
	int	x;
	int	y;

	drawscene(scene, scene->img);
    printf("scene->mlx = %p\n", scene->mlx);
    printf("scene->win = %p\n", scene->win);
    int ret = mlx_mouse_get_pos(scene->mlx, scene->win, &x, &y);
    printf("ret = %d\n", ret);
    printf("coord : %d, %d\n", x, y);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
	return (1);
}
 */

/* int	mouse_click(t_scene *scene)
{
	int	ret;
	int	x;
	int	y;

	printf("coucou\n");
	if (keycode == 1)
	{
		printf("coucou\n");
		(void)scene;
// 		printf("scene->mlx = %p\n", scene->mlx);
		printf("scene->win = %p\n", scene->win);
		ret = mlx_mouse_get_pos(scene->mlx, scene->win, &x, &y);
		printf("ret = %d\n", ret);
		printf("coord : %d, %d\n", x, y);
 	}
	return (0);
} */

static void	handle_move(t_scene *scene, int x, int y, int keycode)
{
	t_ray	r;
	t_inter	i;
	t_elem	*obj;

	r = ray_for_pixel(*(scene->cam), x, y);
	i = intersect_world(scene, r);
	if (i.t < 0)
	{
		return ;
	}
	obj = i.obj;
	printf("obj.pos.y = %f\n", i.obj->w_pos.y);
	if (keycode == UP_ARROW)
	{
		// obj doit etre un pointeur pour recup l adresse de lobjet et relancer draw avec sa nouvelle position
		//dereferencer et envoyer copies pour les calculs, ou envoyer a chaque fois l'adresse et dereferencer dans chaque calcul
		++obj->w_pos.y;
		if (obj->id.shape == sphere)
			obj->transform = matrix_mult(translation(obj->w_pos.x, obj->w_pos.y, obj->w_pos.z), \
									scaling(obj->specs.radius, obj->specs.radius, obj->specs.radius));
	}
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
}

static bool	is_dir_key(int keycode)
{
	return ((keycode >= LEFT_ARROW && keycode <= DOWN_ARROW) || keycode == W_KEY
		|| keycode == A_KEY || keycode == S_KEY || keycode == D_KEY);
}

int	key_hook(int keycode, t_scene *scene)
{
	static int	x = 0;
	static int	y = 0;
	static bool	space = 0;

	if (keycode == ECHAP_KEY)
		close_window(scene);
	else if (keycode == SPACE_KEY)
	{
		printf("to translate : use the arrows (1 click to translate the position of 0.1\n");
		printf("to rotate : use de WASD keys (same scaling)\n");
		mlx_mouse_get_pos(scene->mlx, scene->win, &x, &y);
		space = 1;
	}
	else if (space)
	{
		if (is_dir_key(keycode))
			handle_move(scene, x, y, keycode);
		else
			printf("not a moving key. please restart\n");
		x = 0;
		y = 0;
		space = 0;
	}
/*  	else
		printf("keypressed: %d\n", keycode); */
/* 	else if (keycode == C_KEY)
	{
		input[0] = keycode;
	}
	else if (keycode == 121 && input[0] == C_KEY)
	{
		printf("CY !!\n");
		input[0] = ' ';
	} */
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	launch_display(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		exit_clear(error_display("malloc error"), scene);
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	scene->img = malloc(sizeof(t_img));
	if (!scene->img)
		exit_clear(error_display("malloc error"), scene);
	scene->img->ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img->addr = mlx_get_data_addr(scene->img->ptr, \
		&scene->img->bpp, &scene->img->line_length, \
		&scene->img->endian);
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
	mlx_hook(scene->win, 17, 0, close_window, scene);
//	mlx_hook(scene->win, 4, 0, mouse_click, scene);
	mlx_key_hook(scene->win, key_hook, scene);
//	mlx_mouse_hook(scene->win, mouse_hook, scene);
//	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_loop(scene->mlx);
}
