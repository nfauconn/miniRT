/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clang_attr.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:36:56 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/04 18:20:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLANG_ATTR_H
# define CLANG_ATTR_H

typedef float __attribute__((ext_vector_type(4)))	t_float4;
typedef t_float4									t_point;
typedef t_float4									t_vector;
typedef t_float4									t_rgb;
typedef int __attribute__((ext_vector_type(4)))		t_int4;
typedef float __attribute__((matrix_type(4, 4)))	t_m4x4_f;
typedef t_m4x4_f									t_m3x3_f;
typedef int __attribute__((matrix_type(4, 4)))		t_m4x4_i;

#endif