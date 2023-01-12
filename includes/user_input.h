/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:58:40 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/12 16:58:48 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUT_H
# define USER_INPUT_H

# include "minirt.h"
# include "setup.h"
# include "error.h"

bool	change_obj(t_elem *obj, int keycode);
bool	resize_obj(t_elem *obj, int keycode);
bool	rotate_obj(t_elem *obj, int keycode);
bool	translate_obj(t_elem *obj, int keycode);
void	change_obj_transform_matr(t_elem *obj);
void	handle_move(t_scene *scene, int keycode);
bool	click_hits(t_scene *scene, int x, int y);

/* UTILS */
bool	is_valid_key(int keycode);
bool	is_translate(int keycode);
bool	is_rotate(int keycode);

#endif