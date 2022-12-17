/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:03:30 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/17 18:12:15 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

t_material	default_material(t_elem *elem)
{
	t_material	material;

	material.color = elem->color;
	material.ambient = 0.1;
	material.diffuse = 0.7;
	material.specular = 0.3;
	material.shininess = 200.0;
	return (material);
}

