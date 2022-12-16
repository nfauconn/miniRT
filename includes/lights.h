/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:58:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 12:58:26 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "tuple.h"
# include "matrix.h"
# include "ray.h"
# include "inter.h"

t_vector	normal_at(t_elem *obj, t_point point);
void		prepare_computations(t_inter *i, t_ray ray);
t_vector	reflect(t_vector in, t_vector normal);
void		point_light(t_elem *light, t_point pos, t_rgb color);
t_rgb		lighting(t_material m, t_elem *light, t_point pos, t_vector eyev, \
											t_vector normalv, bool in_shadow);
bool		is_shadowed(t_scene *scene, t_point	point);
t_rgb		shade_hit(t_scene *world, t_inter inter);

#endif