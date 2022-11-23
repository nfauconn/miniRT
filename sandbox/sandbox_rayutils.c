/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:08:51 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/22 18:42:40 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_inter	*create_inter(float t, t_obj obj)
{
	t_inter	*i;

	i = malloc(sizeof(t_inter));
	if (!i)
		return (NULL);
	i->t = t;
	i->obj = obj;
	return (i);
}

void	interaddback(t_inter **head, t_inter *new)
{
	t_inter	*tmp;

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

void	free_interlst(t_inter **lst)
{
	t_inter	*to_free;

	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		free(to_free);
	}
}