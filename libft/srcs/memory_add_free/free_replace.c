/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:15:55 by noe               #+#    #+#             */
/*   Updated: 2022/11/12 13:15:17 by nfauconn         ###   ########.fr       */
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
