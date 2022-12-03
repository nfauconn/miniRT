/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:58:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/02 14:16:52 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "extern_libs.h"
# include "tuple.h"

# include "ray.h" //for init_sphere at least so remove after?

t_vector	normal_atsphere(t_elem sphere, t_point point);

#endif