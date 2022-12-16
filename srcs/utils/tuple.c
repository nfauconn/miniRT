/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:34:33 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/16 18:31:30 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuple.h"

t_float4	create_point(float x, float y, float z)
{
	t_float4	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 1.0;
	return (point);
}

t_float4	create_vector(float x, float y, float z)
{
	t_float4	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 0.0;
	return (point);
}

/* verifie que les deux tuples en arguments on les memes valeurs
a une precision de 0.00001 */
bool	same_tuple(t_float4 tup1, t_float4 tup2)
{
	if (fabs(tup1.x - tup2.x) > EPSILON || fabs(tup1.y - tup2.y) > EPSILON
		|| fabs(tup1.z - tup2.z) > EPSILON || fabs(tup1.w - tup2.w) > EPSILON)
		return (0);
	return (1);
}

/* verifie si un tuple de bolleen a un element valant 0 --> fail */
bool	tuple_bool(t_int4 tuple)
{
	if (tuple.x == 0 || tuple.y == 0 || tuple.z == 0 || tuple.w == 0)
		return (0);
	return (1);
}

/* verifie que les deux arguments float ont la meme valeur,
avec 0.00001 de precision(EPSILON)*/
bool	same_float(float f1, float f2)
{
	if (fabs(f1 - f2) > EPSILON)
		return (0);
	return (1);
}

/* calcul et renvoi la somme du carre de tout les elements d'un tuple
etape pour calculer longueur d'un vecteur */
float	addition_of_squared_elements(t_float4 vector)
{
	return ((vector.x * vector.x) \
		+ (vector.y * vector.y) \
		+ (vector.z * vector.z) \
		+ (vector.w * vector.w));
}

/* longueur ou "Magnitude" d'un vecteur
simple application du theoreme de Pythagore
mais sur des points a 3 voir 4 dimensions
used for view transformation, calculating a Normal, and basix ray-casting */
float	length(t_float4 vector)
{
	float	res;

	res = sqrt(addition_of_squared_elements(vector));
	return (res);
}

/* normalise un vecteur donne pour creer
un nouveau vecteur avec la meme direction,
mais avec un magnitude (longueur) de 1
used for scaling calculs to same proportions */
t_float4	normalize(t_float4 vector)
{
	t_float4	res;

	res = vector / length(vector);
	return (res);
}

/* cree un float resultant de la multiplication de deux vecteur
used for calculating the angle between to vectors
and the "cosine" between two unit vector */
float	dot_product(t_float4 tup1, t_float4 tup2)
{
	return ((tup1.x * tup2.x) \
		+ (tup1.y * tup2.y) \
		+ (tup1.z * tup2.z) \
		+ (tup1.w * tup2.w));
}

float	dot3(t_float4 tup1, t_float4 tup2)
{
	return ((tup1.x * tup2.x) \
		+ (tup1.y * tup2.y) \
		+ (tup1.z * tup2.z));
}

/* cree un vecteur resultant de la multiplication de deux vecteur
used to get the vector that is perpendicular to the other two vector
cross_product(x, y) give z but cross_product(y, x) give -z */
t_float4	cross_product(t_float4 tup1, t_float4 tup2)
{
	t_float4	res;

	res.x = tup1.y * tup2.z - tup1.z * tup2.y;
	res.y = tup1.z * tup2.x - tup1.x * tup2.z;
	res.z = tup1.x * tup2.y - tup1.y * tup2.x;
	res.w = 0;
	return (res);
}
