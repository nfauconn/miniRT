/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:46:00 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/11 14:59:23 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

float	convert_color_to_unit(float unsigned_c)
{
	float	res;

	res = unsigned_c / 255;
	return (res);
}

float	convert_unit_to_rgb(float unit)
{
	float	res;

	res = unit * 255;
	if (unit * 255 - res >= 0.5)
		res += 1;
	if (res > 255)
		res = 255;
	if (res < 0)
		res = 0;
	return (res);
}

int	rgbvtoi(t_float4 color_vec)
{
	int	r;
	int	g;
	int	b;

	r = convert_unit_to_rgb(color_vec.x);
	g = convert_unit_to_rgb(color_vec.y);
	b = convert_unit_to_rgb(color_vec.z);
	return (r << 16 | g << 8 | b);
}

void	adjust_light(t_rgb *color)
{
	if (color->x > 1)
		color->x = 1;
	if (color->y > 1)
		color->y = 1;
	if (color->z > 1)
		color->z = 1;
}
