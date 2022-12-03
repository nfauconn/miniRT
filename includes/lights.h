/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:58:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/03 19:01:26 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "extern_libs.h"
# include "tuple.h"
# include "matrix.h"

# include "ray.h" //for init_sphere  at least : remove after ?

t_vector	normal_atsphere(t_elem *sp, t_point point);
t_vector	reflect(t_vector in, t_vector normal);
void		point_light(t_elem *light, t_point pos, float ratio);
t_material	default_material();
t_rgb		lighting(t_material m, t_elem light, t_point pos, t_vector eyev, t_vector normalv);

#endif