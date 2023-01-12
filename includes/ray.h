/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:11:12 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/12 16:57:25 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

t_ray		ray(t_point orig, t_vector dir);
t_point		position(t_ray ray, float t);
t_ray		transform_ray(t_ray prev_r, t_m4x4_f matrix);
void		set_transform(t_elem *obj, t_m4x4_f transfo_matrix);

#endif