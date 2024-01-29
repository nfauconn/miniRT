/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:45:03 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/13 15:48:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_H
# define INTER_H

# include "minirt.h"
# include "matrix.h"
# include "ray.h"

t_inter	intersect_world(t_scene *world, t_ray ray);
t_point	position(t_ray ray, float t);
t_inter	intersection(float t, t_elem *obj);
t_inter	hit(t_xs xs);
t_xs	intersect(t_elem *obj, t_ray r);

t_xs	pl_intersect(t_elem p, t_ray r);

t_xs	sp_intersect(t_elem s, t_ray r);

float	cylinder_min(t_elem cyl);
float	cylinder_max(t_elem cyl);
t_xs	local_intersect_cyl(t_elem cyl, t_ray ray);

#endif