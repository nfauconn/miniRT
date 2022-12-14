/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:41 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/14 17:16:32 by nfauconn         ###   ########.fr       */
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

static float	small(char *str)
{
	float	res;
	int		j;

	j = 1;
	res = 0;
	while (ft_isdigit(str[0]))
	{
		res += (str[0] - '0') * neg_exponant(j++);
		str++;
	}
	return (res);
}

float	ft_atof(char *str)
{
	float	res;
	int		neg;
	int		i;

	while (ft_iswhitespace(str[0]))
		str++;
	i = 0;
	neg = 1;
	if (str[0] == '-')
	{
		neg = -1;
		str++;
	}
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	res += small(str + i);
	return (res * neg);
}
