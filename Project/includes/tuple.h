/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:12:15 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:18:22 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include "minirt.h"
# include "externlibs.h"

enum e_point_vector
{
	vec = 0,
	pt
};

t_float4	create_point(float x, float y, float z);
t_float4	create_vector(float x, float y, float z);
bool		same_tuple(t_float4 tup1, t_float4 tup2);
bool		tuple_bool(t_int4 tuple);
bool		same_float(float f1, float f2);
float		addition_of_squared_elements(t_float4 vector);
float		length(t_float4 vector);
t_float4	normalize(t_float4 vector);
float		dot_product(t_float4 tup1, t_float4 tup2);
float		dot_product(t_float4 tup1, t_float4 tup2);
t_float4	cross_product(t_float4 tup1, t_float4 tup2);

#endif