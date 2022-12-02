/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:02:04 by noe               #+#    #+#             */
/*   Updated: 2022/12/02 13:24:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	elem_add_back(t_elem **head, t_elem *to_add, uint8_t shape, ssize_t no)
{
	t_elem *elem;

	if (!*head)
	{
		*head = to_add;
		to_add->next = NULL;
		return ;
	}
	elem = *head;
	while (elem->next)
		elem = elem->next;
	elem->next = to_add;
	to_add->id.shape = shape;
	to_add->id.no = no;
	to_add->next = NULL;
}