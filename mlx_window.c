/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:16:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/27 14:24:37 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "mlx/mlx.h"

typedef struct s_libwin
{
	void				*mlx;
	void				*win;
	void				**img[2];
	//struct s_mapdata	scene;
}				t_libwin;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	wincloser(t_libwin *libwin)
{
	size_t	i;

	i = 0;
	while (i < 1)//need check if img exist
	{
		if (libwin->img[i])
		{
			mlx_destroy_image(libwin->mlx, libwin->img[i]);
		}
		i++;
	}
	if (libwin->win)
		mlx_destroy_window(libwin->mlx, libwin->win);
	mlx_destroy_display(libwin->mlx);
	free(libwin->mlx);
	exit(0);
}

int	keyparser(int keycode, t_libwin *libwin)
{
	if (keycode == 65307)
		wincloser(libwin);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	fill_img(t_data data, int color)
{
	int	i;
	int	j;
	i = 0;
	while (i <= 1200)
	{
		j = 0;
		while (j <= 1024)
		{
			my_mlx_pixel_put(&data, i, j, color);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_libwin	libwin;
	t_data	img;

	libwin.mlx = mlx_init();
	libwin.win = mlx_new_window(libwin.mlx, 1200, 1024, "MiniRT");

	img.img = mlx_new_image(libwin.mlx, 1200, 1024);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	fill_img (img, 0x00FF0000);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	libwin.img[0] = img.img;
	/*function need mlx instance, windows, img, position start*/
	mlx_put_image_to_window(libwin.mlx, libwin.win, libwin.img[0], 0, 0);
	mlx_hook(libwin.win, 2, 1L << 0, keyparser, &libwin);
	mlx_hook(libwin.win, 17, 1L << 2, wincloser, &libwin);
	mlx_loop(libwin.mlx);
}
