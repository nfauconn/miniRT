/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:41 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/10 06:39:30 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	neg_exponant(int j)
{
	float	res;

	res = 1;
	while (j > 0)
	{
		res /= 10;
		j--;
	}
	return (res);
}

static float	small(char c, int j)
{
	float	res;

	res = c - '0';
	res *= neg_exponant(j);
	return (res);
}

float	ft_atof(char *str)
{
	float	res;
	int		i;
	int		j;

	while (ft_iswhitespace(str[0]))
		str++;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	j = 1;
	while (ft_isdigit(str[i]))
	{
		res += small(str[i], j);
		j++;
		i++;
	}
	return (res);
}
