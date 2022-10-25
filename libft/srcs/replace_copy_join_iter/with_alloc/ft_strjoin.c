/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:04:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/25 18:03:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	newlen;
	size_t	i;
	size_t	j;

	newlen = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof (char) * (newlen + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}