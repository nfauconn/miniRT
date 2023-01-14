/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:44:19 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/14 17:05:14 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	close_window(t_scene *scene)
{
	if (scene->img->ptr)
		mlx_destroy_image(scene->mlx, scene->img->ptr);
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene->mlx);
	exit_clear(0, scene);
	return (0);
}

int	key_hook(int keycode, t_scene *scene)
{
	static int	dir_key = 0;

	if (keycode == ECHAP_KEY)
		close_window(scene);
	else if (scene->move.asked && is_dir_key(keycode))
		dir_key = keycode;
	else if (scene->move.asked && dir_key && ft_isdigit(keycode))
	{
		keycode -= 48;
		handle_move(scene, dir_key, keycode);
		dir_key = 0;
	}
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
