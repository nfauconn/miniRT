/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:45:03 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/10 18:58:26 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_H
# define INTER_H

# include "minirt.h"
# include "matrix.h"
# include "ray.h"

float	cylinder_min(t_elem cyl);
float	cylinder_max(t_elem cyl);
t_inter	intersect_world(t_scene *world, t_ray ray);
t_point	position(t_ray ray, float t);
t_inter	intersection(float t, t_elem *obj);
t_inter	hit(t_xs xs);
t_xs	intersect(t_elem *obj, t_ray r);
t_xs	sp_intersect(t_elem s, t_ray r);

#endif