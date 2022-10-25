/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:30:54 by noe               #+#    #+#             */
/*   Updated: 2022/10/25 18:07:03 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarraydup(char **strarray)
{
	char	**ret;
	ssize_t	size;
	size_t	i;

	size = ft_strarraysize(strarray);
	ret = (char **)malloc(sizeof (char *) * (size + 1));
	i = 0;
	while (strarray[i])
	{
		ret[i] = ft_strdup(strarray[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
