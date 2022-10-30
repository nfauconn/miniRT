/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/30 17:04:41 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


int	main(int ac, char **av)
{
/* 	if (ac != 2)
		return (error_display("please enter a scene file"));
	parse(av[1]); */

	(void)ac;
	(void)av;
	t_window	w;
	t_img	img;
	t_scene scene;

	w.mlx = mlx_init();
	w.ptr = mlx_new_window(w.mlx, WIDTH, HEIGHT, "MiniRT");
	img.ptr = mlx_new_image(w.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_length,
								&img.endian);
	scene = scene_setup();
	fill_img (img, scene);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	w.img[0] = img.ptr;
	/*function need mlx instance, windows, img, position start*/
	mlx_put_image_to_window(w.mlx, w.ptr, w.img[0], 0, 0);
	mlx_hook(w.ptr, 2, 1L << 0, keyparser, &w);
	mlx_hook(w.ptr, 17, 1L << 2, wincloser, &w);
	mlx_loop(w.mlx);
	return (0);
}
