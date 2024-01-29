/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:58:29 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:08:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "tuple.h"
# include "matrix.h"
# include "ray.h"
# include "inter.h"
# include "rgb.h"

typedef struct s_lighting
{
	t_rgb		effective_color;
	t_vector	reflectv;
	float		cos_reflectv_eyev;
	t_vector	lightv;
	float		cos_lightv_normalv;
	t_rgb		ambient;
	t_rgb		diffuse;
	t_rgb		specular;
	float		factor;
}	t_lighting;

t_vector	normal_at(t_elem *obj, t_point point);
void		prepare_computations(t_inter *i, t_ray ray);
t_vector	reflect(t_vector in, t_vector normal);
t_rgb		lighting(t_scene *scene, t_elem *light, t_inter inter, bool shadow);
bool		is_shadowed(t_scene *scene, t_elem *light, t_point	point);
t_rgb		shade_hit(t_scene *world, t_inter inter);

#endif