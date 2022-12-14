/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:58:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 18:52:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "extern_libs.h"
# include "defines.h"
# include "structs.h"
# include "tuple.h"
# include "matrix.h"
# include "ray.h"
# include "scene.h"

t_vector	normal_at(t_elem *obj, t_point point);
t_vector	reflect(t_vector in, t_vector normal);
void		point_light(t_elem *light, t_point pos, t_rgb color);
t_material	default_material(t_elem *elem);
t_rgb		lighting(t_material m, t_elem *light, t_point pos, t_vector eyev, \
											t_vector normalv, bool in_shadow);
bool	is_shadowed(t_scene *scene, t_point	point);

#endif