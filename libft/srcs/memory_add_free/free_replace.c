/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replacefree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:15:55 by noe               #+#    #+#             */
/*   Updated: 2022/10/25 18:08:46 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_replace(char **old, char *new)
{
	char	*tmp;

	tmp = *old;
	*old = new;
	if (tmp)
		free(tmp);
	return (NULL);
}
