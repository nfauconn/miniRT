/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:58:40 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/13 15:37:03 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUT_H
# define USER_INPUT_H

# include "minirt.h"
# include "setup.h"
# include "error.h"

/* PARSING */
bool	is_valid_key(int keycode);
bool	is_translate(int keycode);
bool	is_rotate(int keycode);
bool	click_hits(t_scene *scene, int x, int y);

bool	change_obj(t_elem *obj, int keycode);
bool	resize_obj(t_elem *obj, int keycode);
bool	rotate_obj(t_elem *obj, int keycode);
bool	translate_obj(t_elem *obj, int keycode);
void	handle_move(t_scene *scene, int keycode);

#endif