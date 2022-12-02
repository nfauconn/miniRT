/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:50:55 by noe               #+#    #+#             */
/*   Updated: 2022/12/02 13:29:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clear_lst(t_elem **lst)
{
	t_elem	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free);
	}
}

void	clear(t_scene *scene)
{
	if (scene->img)
		free(scene->img);
	if (scene->amblight)
		clear_lst(&scene->amblight);
	if (scene->cam)
		clear_lst(&scene->cam);
	if (scene->lights)
		clear_lst(&scene->lights);
	if (scene->objs)
		clear_lst(&scene->objs);
	if (scene->mlx)
		free(scene->mlx);
}

void	exit_clear(bool exit_code, t_scene *scene)
{
	clear(scene);
	exit(exit_code);
}
