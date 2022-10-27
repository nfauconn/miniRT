/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:14:40 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/27 19:18:01 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef float float3 __attribute__((ext_vector_type(3)));

int	main(void)
{
	float3 x;

    float3 vec = (float3){1.0, 2.0, 3.0};
    printf("Notre vecteur = %f %f %f\n", vec.x, vec.y, vec.z);
	
	return (0);
}

float3	ray_pos(float3 origin, float3 direction, float t)
{
	float3 position;
	
	position = origin + t * direction;
	return (position);
}

int	ray_color(float3 ray_direction)
{
    float t;

	t = 0.5*(ray_direction.y() + 1.0);
    return ((1.0-t)*0x00FFFFFF + t*0x0000CCFF);
}

// ! need vector length


float3 unit_vector(float3 v)
{
	float3 res;

	res = v / length(v);
	return (res);
}

int	truc(void)
{
	//here change depending from pixel concerned
	float3 ray_direction;
	ray_direction = lower_left_corner + u*horizontal + v*vertical - origin;
	int	color = ray_color(ray_direction);
}