/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:50:55 by noe               #+#    #+#             */
/*   Updated: 2022/11/07 22:43:19 by noe              ###   ########.fr       */
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

void	exit_clear(t_bool exit_code, t_scene *scene)
{
	if (scene->lights)
		clear_lst(&scene->lights);
	if (scene->sp)
		clear_lst(&scene->sp);
	if (scene->cy)
		clear_lst(&scene->cy);
	if (scene->pl)
		clear_lst(&scene->pl);
	free(scene);
	scene = NULL;
	exit(exit_code);
}
