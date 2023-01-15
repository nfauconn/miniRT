/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:55:10 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/15 22:59:10 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minirt.h"
# include "scene.h"
# include "rgb.h"
# include "error.h"
# include "exit.h"
# include "ray.h"
# include "inter.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		close_window(t_scene *scene);
int		key_hook(int keycode, t_scene *scene);
void	launch_display(t_scene *scene);
void	drawscene(t_scene *scene, t_img *img);
void	render(t_scene *scene, t_img *img);

#endif