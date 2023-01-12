/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:50:49 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/12 16:50:50 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"
# include "ray.h"
# include "lights.h"

t_rgb		create_color(float red, float green, float blue);
t_rgb		color_at(t_scene *world, t_ray ray);

#endif