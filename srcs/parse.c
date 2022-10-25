/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:11:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/25 16:48:37 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	correct_filename(char *s)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (!ft_strend_cmp(s, ".rt"))
		return (0);
	i = 0;
	while (s[i] && i < len - 3)
	{
		if (!is_identifier(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse(char *scene)
{
	if (!correct_filename(scene))
		exit (error_display("invalid scene file -> format : *.rt"));
	
}
