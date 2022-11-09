/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:21:41 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/09 18:28:57 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	neg_exponant(int j)
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

float	small(char c, int j)
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

	while (ft_iswhitespace(str[0]) == 1)
		str++;
	i = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	j = 1;
	while (ft_isdigit(str[i]) == 1)
	{
		res += small(str[i], j);
		j++;
		i++;
	}
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	float	test;

// 	test = ft_atof("0.3");
// 	printf("%f\n", test);
// 	return (0);
// }