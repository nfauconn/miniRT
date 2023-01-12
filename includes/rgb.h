/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:57:42 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/12 16:57:47 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include "minirt.h"

float		convert_color_to_unit(float unsigned_c);
float		convert_unit_to_rgb(float unit);
int			rgbvtoi(t_float4 color_vec);
void		adjust_light(t_rgb *color);

#endif