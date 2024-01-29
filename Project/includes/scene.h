/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:09:30 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/17 18:45:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "tuple.h"
# include "matrix.h"
# include "display.h"
# include "lights.h"
# include "ray.h"
# include "color.h"

void		drawscene(t_scene *scene, t_img *img);
t_m4x4_f	view_transform(t_point from, t_point to, t_vector up);
t_ray		ray_for_pixel(t_camera cam, float px, float py);
void		render(t_scene *scene, t_img *img);

#endif