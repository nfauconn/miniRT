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

static void	reset_move(t_scene *scene)
{
	scene->move.asked = 0;
	scene->move.obj = NULL;
}

int	mouse_click(int keycode, int x, int y, t_scene *scene)
{
	if (keycode == LEFT_CLICK)
	{
		set_move(scene, x, y);
		printf("\nobject selected\n");
	}
	else
	{
		reset_move(scene);
		printf("object unselected\n");
	}
	return (0);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ECHAP_KEY)
		close_window(scene);
	else if (scene->move.asked && is_dir_key(keycode))
		handle_move(scene, keycode);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	print_instructions(void)
{
	printf("\nwelcome\n");
	printf("left click on an object to :\n");
	printf("\t- resize it (+/- keys)\n");
	printf("\t- translate it (arrow keys)\n");
	printf("\t- rotate it (WASD keys)\n");
	printf("use any other mouse click to unselect the object\n\n");
	printf("drawing initial scene...\n");
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
	print_instructions();
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
	mlx_hook(scene->win, 17, 0, close_window, scene);
	mlx_key_hook(scene->win, key_hook, scene);
	mlx_mouse_hook(scene->win, mouse_click, scene);
	mlx_loop(scene->mlx);
}
