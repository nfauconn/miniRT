/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:02:04 by noe               #+#    #+#             */
/*   Updated: 2022/11/10 13:05:46 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	elem_add_back(t_element **head, t_element *to_add)
{
	t_element *elem;

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