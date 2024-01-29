/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:30:54 by noe               #+#    #+#             */
/*   Updated: 2023/01/12 17:07:09 by fjeiwjifeoh      ###   ########.fr       */
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
