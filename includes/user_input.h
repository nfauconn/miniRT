/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:58:40 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/15 22:38:15 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUT_H
# define USER_INPUT_H

# include "minirt.h"
# include "setup.h"
# include "error.h"

/* PARSING */
bool	is_value_key(int keycode);
bool	is_axis_key(int keycode);
bool	is_id_key(int keycode);
bool	click_hits(t_scene *scene, int x, int y);
void	move_parse(t_scene *scene, int keycode);

/* APPLYING */
bool	change_obj(t_scene *scene);
bool	resize_obj(t_scene *scene);
bool	rotate_obj(t_scene *scene);
bool	translate_obj(t_scene *scene);
void	handle_obj_move(t_scene *scene);
void	handle_cam_move(t_scene *scene);

#endif