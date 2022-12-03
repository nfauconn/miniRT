/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:02:04 by noe               #+#    #+#             */
/*   Updated: 2022/12/03 17:25:16 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuple.h"

void	elem_add_back(t_elem **head, t_elem *to_add)
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
	to_add->next = NULL;
}