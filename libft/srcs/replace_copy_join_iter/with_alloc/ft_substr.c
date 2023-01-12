/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:05:40 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/12 17:06:04 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *source, size_t start, size_t len)
{
	char	*new;
	size_t	sourcelen;
	size_t	i;

	sourcelen = ft_strlen(source);
	if (!len || start > sourcelen)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (source[start] && i < len)
		new[i++] = source[start++];
	new[i] = '\0';
	return (new);
}
