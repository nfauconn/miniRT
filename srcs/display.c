#include "minirt.h"

int	wincloser(t_window *w)
{
	size_t	i;

	i = 0;
	while (i < 1)//need check if img exist
	{
		if (w->img[i])
		{
			mlx_destroy_image(w->mlx, w->img[i]);
		}
		i++;
	}
	if (w->ptr)
		mlx_destroy_window(w->mlx, w->ptr);
	mlx_destroy_display(w->mlx);
	free(w->mlx);
	exit(0);
}

int	keyparser(int keycode, t_window *w)
{
	if (keycode == 65307)
		wincloser(w);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	display_scene(t_scene scene)
{
	t_window	w;
	t_img	img;

	w.mlx = mlx_init();
	w.ptr = mlx_new_window(w.mlx, WIDTH, HEIGHT, "MiniRT");
	img.ptr = mlx_new_image(w.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_length,
								&img.endian);
	fill_img (img, scene);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	w.img[0] = img.ptr;
	/*function need mlx instance, windows, img, position start*/
	mlx_put_image_to_window(w.mlx, w.ptr, w.img[0], 0, 0);
	mlx_hook(w.ptr, 2, 1L << 0, keyparser, &w);
	mlx_hook(w.ptr, 17, 1L << 2, wincloser, &w);
	mlx_loop(w.mlx);
}