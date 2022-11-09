/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:50:55 by noe               #+#    #+#             */
/*   Updated: 2022/11/09 14:21:27 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clear_lst(t_element **lst)
{
	t_element	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free);
		printf("*lst = %p\n", *lst);
	}
}

void	clear(t_scene *scene)
{
	if (!scene)
		return ;
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
