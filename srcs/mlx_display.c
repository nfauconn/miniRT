#include "miniRT.h"

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
