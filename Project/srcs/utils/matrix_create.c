/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:22:31 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:54:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_m4x4_f	matrix_4xf_create(float *f)
{
	t_m4x4_f	matrix;
	int			j;
	int			k;
	int			i;

	i = 0;
	j = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			matrix[j][k] = f[i++];
			k++;
		}
		j++;
	}
	return (matrix);
}

t_m3x3_f	matrix_3xf_create(float *f)
{
	t_m3x3_f	matrix;
	int			j;
	int			k;
	int			i;

	i = 0;
	j = 0;
	while (j < 3)
	{
		k = 0;
		while (k < 3)
		{
			matrix[j][k] = f[i++];
			k++;
		}
		j++;
	}
	return (matrix);
}

t_m4x4_f	identity_matr(void)
{
	float		tabf[16];
	t_m4x4_f	matrix;

	ft_bzero(tabf, sizeof(tabf));
	matrix = matrix_4xf_create(tabf);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
	return (matrix);
}
