/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:08:51 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/19 23:14:31 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_intersection	*create_intersection(float t, t_obj obj)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
	if (!i)
		return (NULL);
	i->t = t;
	i->obj = obj;
	return (i);
}

void	interaddback(t_intersection **head, t_intersection *new)
{
	t_intersection	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
}

void	free_interlst(t_intersection **lst)
{
	t_intersection	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free);
	}
}