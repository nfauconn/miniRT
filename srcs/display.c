/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:44:19 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/15 20:44:25 by nfauconn         ###   ########.fr       */
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
	if (keycode == ECHAP_KEY)
		close_window(scene);
	if (keycode == CAMERA)
	{
		scene->move.asked = 1;
		scene->move.cam = scene->cam;
		scene->move.obj = NULL;
		printf("camera selected\nchoose your move:\n");
		printf("\t-translation (t)\n");
		printf("\t-rotation (r)\n");
	}
	else if (scene->move.asked && is_id_key(keycode))
	{
		if (scene->move.cam && keycode == 's')
			scene->move.id = 0;
		else
		{
			scene->move.id = keycode;
			if (scene->move.id == 's')
				printf("s selected. please choose the value\n");
			else
				printf("%c selected. you can now choose the axis x, y or z\n", keycode);
		}
	}
	else if (scene->move.asked && scene->move.id && is_axis_key(keycode))
	{
		scene->move.axis = keycode;
		printf("%c selected. you can now choose the value btw -9 & 9 units\n", keycode);
	}
	else if (scene->move.asked && scene->move.id && (scene->move.axis || scene->move.id == 's')
		&& keycode == '-')
	{
		scene->move.neg = '-';
	}
	else if (scene->move.asked && scene->move.id && (scene->move.axis || scene->move.id == 's')
		&& is_value_key(keycode))
	{
		scene->move.value = keycode - 48;
		if (scene->move.neg)
			scene->move.value = -scene->move.value;
		printf("%c%c chosen\n", scene->move.neg, keycode);
		scene->move.neg = 0;
		if (scene->move.obj)
			handle_obj_move(scene);
		else if (scene->move.cam)
			handle_cam_move(scene);
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
	printf("\t-left click on an object to apply changes\n");
	printf("\t-tap C to change camera\n");
	printf("\t-use mouse right click to cancel\n");
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
