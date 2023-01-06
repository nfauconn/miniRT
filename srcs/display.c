#include "display.h"

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

int	parse_key(int keycode, t_scene *scene)
{
	static	char input[3] = "  ";

	if (keycode == 65307)
		close_window(scene);
	else if (keycode == C_KEY)
	{
		input[0] = keycode;
	}
	else if (keycode == 121 && input[0] == C_KEY)
	{
		printf("CY !!\n");
		input[0] = ' ';
	}
/* 	else
		printf("keypressed: %d\n", keycode); */
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* static int	render_next_frame(t_scene *scene)
{
 	if (get_input(scene))
	{
		get_input(scene);
		drawscene(scene, scene->img);
		mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
 	}
	return (1);
} */

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
	mlx_key_hook(scene->win, parse_key, scene);
	mlx_hook(scene->win, 17, 0, close_window, scene);
//	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_loop(scene->mlx);
}

void	render(t_scene *scene, t_img *img)
{
	size_t		x;
	size_t		y;
	t_ray		r;
	t_rgb		color;

	y = 0;
	while (y < scene->cam->vsize)
	{
		x = 0;
		while (x < scene->cam->hsize)
		{
			r = ray_for_pixel(*(scene->cam), x, y);
			color = color_at(scene, r);
			my_mlx_pixel_put(img, x, y, rgbvtoi(color));
			x++;
		}
		y++;
	}
	printf("finish\n");
}