/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:50:55 by noe               #+#    #+#             */
/*   Updated: 2022/11/08 19:38:37 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clear_lst(t_element **lst)
{
	t_element	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	clear(t_scene *scene)
{
	if (scene->A)
		clear_lst(&scene->A);
	if (scene->C)
		clear_lst(&scene->C);
	if (scene->lights)
		clear_lst(&scene->lights);
	if (scene->sp)
		clear_lst(&scene->sp);
	if (scene->cy)
		clear_lst(&scene->cy);
	if (scene->pl)
		clear_lst(&scene->pl);
}

void	exit_clear(t_bool exit_code, t_scene *scene)
{
	clear(scene);
	exit(exit_code);
}
