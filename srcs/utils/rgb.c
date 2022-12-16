/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:46:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 16:46:03 by nfauconn         ###   ########.fr       */
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

int rgbvtoi(t_float4 color_vec)
{
	int	r;
	int	g;
	int	b;

 	r = convert_unit_to_rgb(color_vec.x);
	g = convert_unit_to_rgb(color_vec.y);
	b = convert_unit_to_rgb(color_vec.z);
	return (r << 16 | g << 8 | b);
}
