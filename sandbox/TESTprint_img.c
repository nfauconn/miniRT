/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TESTprint_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:14:40 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/16 12:03:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef float t_float3 __attribute__((ext_vector_type(3)));

int	main(void)
{
	t_float3 x;

    t_float3 vec = (t_float3){1.0, 2.0, 3.0};
    printf("Notre vecteur = %f %f %f\n", vec.x, vec.y, vec.z);
	
	return (0);
}

t_float3	ray_pos(t_float3 origin, t_float3 direction, float t)
{
	t_float3 position;
	
	position = origin + t * direction;
	return (position);
}

int	ray_color(t_float3 ray_direction)
{
    float t;

	t = 0.5*(ray_direction.y() + 1.0);
    return ((1.0-t)*0x00FFFFFF + t*0x0000CCFF);
}

// ! need vector length


t_float3 unit_vector(t_float3 v)
{
	t_float3 res;

	res = v / length(v);
	return (res);
}

int	truc(void)
{
	//here change depending from pixel concerned
	t_float3 ray_direction;
	ray_direction = lower_left_corner + u*horizontal + v*vertical - origin;
	int	color = ray_color(ray_direction);
}

int vtoi(t_float3 vcolor)
{
	int color;
	
	color = vcolor.z * 255;
	color += vcolor.y * 255 * 100;
	color += vcolor.x * 255 * 10000;

	return (color);	
}