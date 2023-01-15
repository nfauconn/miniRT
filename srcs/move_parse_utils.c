/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 22:40:37 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/15 22:56:07 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	is_value_key(int keycode)
{
	return (keycode >= '0' && keycode <= '9');
}

bool	is_axis_key(int keycode)
{
	return (keycode == 'x' || keycode == 'y' || keycode == 'z');
}

bool	is_id_key(int keycode)
{
	return (keycode == 'r' || keycode == 't' || keycode == 's');
}
