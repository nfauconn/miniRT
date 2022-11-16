/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap2_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:10:17 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/13 20:16:39 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include/criterion/criterion.h"
# include <math.h>
# include <stdio.h>
# include <errno.h>

typedef float	t_float3	__attribute__((ext_vector_type(3)));

t_float3	color_create(float r, float g, float b)
{
	t_float3	color_tup;

	color_tup.x = r;
	color_tup.y = g;
	color_tup.z = b;
	return (color_tup);
}

bool	same_float(float f1, float f2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(f1 - f2) > epsilon)
		return (0);
	return (1);
}

bool	same_color(t_float3 tup1, t_float3 tup2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(tup1.x - tup2.x) > epsilon || fabs(tup1.y - tup2.y) > epsilon
		|| fabs(tup1.z - tup2.z) > epsilon)
		return (0);
	return (1);
}

Test(color_test, color_create)
{
	t_float3 color_tup;
	color_tup = color_create(-0.5, 0.4, 1.7);
	cr_expect(same_float(color_tup.x , -0.5) == 1);
	cr_expect(same_float(color_tup.y , 0.4) == 1);
	cr_expect(same_float(color_tup.z , 1.7) == 1);
}

Test(color_test, color_add)
{
	t_float3 tup1 = color_create(0.9, 0.6, 0.75);
	t_float3 tup2 = color_create(0.7, 0.1, 0.25);
	t_float3 tup3 = color_create(1.6, 0.7, 1.0);
	cr_expect(same_color((tup1 + tup2), tup3) == 1);
}
Test(color_test, color_sub)
{
	t_float3 tup1 = color_create(0.9, 0.6, 0.75);
	t_float3 tup2 = color_create(0.7, 0.1, 0.25);
	t_float3 tup3 = color_create(0.2, 0.5, 0.5);
	cr_expect(same_color((tup1 - tup2), tup3) == 1);
}
Test(color_test, color_mult_scal)
{
	t_float3 tup1 = color_create(0.2, 0.3, 0.4);
	t_float3 tup3 = color_create(0.4, 0.6, 0.8);
	cr_expect(same_color((tup1 * 2), tup3) == 1);
}

Test(color_test, color_mult)
{
	t_float3 tup1 = color_create(1, 0.2, 0.4);
	t_float3 tup2 = color_create(0.9, 1, 0.1);
	t_float3 tup3 = color_create(0.9, 0.2, 0.04);
	cr_expect(same_color((tup1 * tup2), tup3) == 1);
}

int vtoi(t_float3 color_vec)
{
	int	r;
	int	g;
	int	b;

	r = color_vec.x * 255;
	if (color_vec.x * 255 - r >= 0.5)
		r += 1;
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	g = color_vec.y * 255;
	if (color_vec.y * 255 - g >= 0.5)
		g += 1;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	b = color_vec.z * 255;
	if (color_vec.z * 255 - b >= 0.5)
		b += 1;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);
}

Test(color_test, convert_int)
{
	t_float3 tup1 = color_create(1.5, 0, 0);
	int	color = vtoi(tup1);
	cr_expect(color == 255 * 256 * 256);

	t_float3 tup2 = color_create(0, 0.5, 0);
	int	color2 = vtoi(tup2);
	cr_expect(color2 == 128 * 256);
	// printf ("color = %d, expected %d\n", color2, 128 * 256);

	t_float3 tup3 = color_create(-0.5, 0, 1);
	int	color3 = vtoi(tup3);
	cr_expect(color3 == 255);

	t_float3 tup4 = color_create(1, 0.8, 0.6);
	int	color4 = vtoi(tup4);
	int	color5 = 255 * 256 * 256 + 204 * 256 + 153;
	cr_expect(color4 == color5);
	//printf ("color = %d, expected %d\n", color, 255 * 256 * 256);
}