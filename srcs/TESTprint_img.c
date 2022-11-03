/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TESTprint_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:14:40 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/03 14:46:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef double double3 __attribute__((ext_vector_type(3)));

int	main(void)
{
	double3 x;

    double3 vec = (double3){1.0, 2.0, 3.0};
    printf("Notre vecteur = %f %f %f\n", vec.x, vec.y, vec.z);
	
	return (0);
}

double3	ray_pos(double3 origin, double3 direction, double t)
{
	double3 position;
	
	position = origin + t * direction;
	return (position);
}

int	ray_color(double3 ray_direction)
{
    double t;

	t = 0.5*(ray_direction.y() + 1.0);
    return ((1.0-t)*0x00FFFFFF + t*0x0000CCFF);
}

// ! need vector length


double3 unit_vector(double3 v)
{
	double3 res;

	res = v / length(v);
	return (res);
}

int	truc(void)
{
	//here change depending from pixel concerned
	double3 ray_direction;
	ray_direction = lower_left_corner + u*horizontal + v*vertical - origin;
	int	color = ray_color(ray_direction);
}

int vtoi(double3 vcolor)
{
	int color;
	
	color = vcolor.z * 255;
	color += vcolor.y * 255 * 100;
	color += vcolor.x * 255 * 10000;

	return (color);	
}