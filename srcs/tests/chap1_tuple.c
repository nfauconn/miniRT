/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap1_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:09:47 by rokerjea          #+#    #+#             */
/*   Updated: 2023/01/11 19:22:02 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/mnt/nfs/homes/rokerjea/Criterion/include/criterion/criterion.h"
#include <math.h>
#include <stdio.h>
#include <errno.h>
#include "tuple.h"
#include "color.h"

typedef float t_float4 __attribute__((ext_vector_type(4)));
typedef int	int4 __attribute__((ext_vector_type(4)));

// int is_equal(float x, float y)
// {
// 	if (x == y)
// 		return (1);
// 	return (0);
// }

bool	is_point(t_float4 tuple)
{
	if (tuple.w == 1.0)
		return (1);
	return(0);
}

bool	is_vector(t_float4 tuple)
{
	if (tuple.w == 1.0)
		return (0);
	return(1);
}

// bool	same_tuple(t_float4 tup1, t_t_float4 tup2)
// {
// 	if (fabs(tup1.x - tup2.x) > EPSILON || fabs(tup1.y - tup2.y) > EPSION
// 		|| fabs(tup1.z - tup2.z) > EPSILON || fabs(tup1.w - tup2.w) > EPSILON)
// 		return (0);
// 	return (1);
// }

// bool	tuple_bool(int4 tuple)
// {
// 	if(tuple.x == 0 || tuple.y == 0 || tuple.z == 0 || tuple.w == 0)
// 		return (0);
// 	return (1);
// }

Test (tuple_test, tuple_point)
{
	t_float4	tuple1 = (t_float4){4.3, -4.2, 3.1, 1.0};
	float x = 4.3;
	float y = -4.2;
	float z = 3.1;
	float w = 1.0;
	cr_expect(tuple1.x == x, "x false");
	cr_expect(tuple1.y == y, "y false");
	cr_expect(tuple1.z == z, "z false");
	cr_expect(tuple1.w == w, "w false");
	cr_expect(is_point(tuple1.w) == 1, "tuple_point is point");
	cr_expect(is_vector(tuple1.w) == 0, "tuple_point is not vector");
}

Test (tuple_test, tuple_vector)
{
	t_float4	tuple2 = (t_float4){4.3, -4.2, 3.1, 0.0};
	float x = 4.3;
	float y = -4.2;
	float z = 3.1;
	float w = 0.0;
	cr_expect(tuple2.x == x, "x false");
	cr_expect(tuple2.y == y, "y false");
	cr_expect(tuple2.z == z, "z false");
	cr_expect(tuple2.w == w, "w false");
	cr_expect(is_point(tuple2.w) == 0, "tuple_vector is not point");
	cr_expect(is_vector(tuple2.w) == 1, "tuple_vector is vector");
}

Test(tuple_test, tuple_factory)
{
	t_float4	tuple1 = (t_float4){4, -4, 3, 1.0};
	t_float4	tuple2;
	tuple2 = create_point(4, -4, 3);
	cr_expect(same_tuple(tuple1, tuple2) == 1, "create point");
	tuple1 = (t_float4){4, 4, 3, 1.0};
	cr_expect(same_tuple(tuple1, tuple2) == 0, "create point");
	tuple1 = (t_float4){4, -4, 3, 0.0};
	t_float4	tuple3;
	tuple3 = create_vector(4, -4, 3);
	cr_expect(same_tuple(tuple1, tuple3) == 1, "create vector");
	tuple1 = (t_float4){4, 4, 3, 1.0};
	cr_expect(same_tuple(tuple1, tuple3) == 0, "create vector");

	int4 fun;
	fun = tuple1 == tuple3;
	cr_expect(tuple_bool(fun) == 0, "compare vector should fail");
	tuple1 = (t_float4){4, -4, 3, 0.0};
	fun = tuple1 == tuple3;
	cr_expect(tuple_bool(fun) == 1, "compare vector should succeed");
	// printf ("%d %d %d %d\n", fun.s0, fun.s1,fun.s2,fun.s3);
}

Test(tuple_test, tuple_operation)
{
	t_float4	tuple1;
	t_float4	tuple2;
	t_float4	tuple3;
	tuple1 = create_point(3, -2, 5);
	tuple2 = create_vector(-2, 3, 1);
	tuple1 = tuple1 + tuple2;
	tuple3 = (t_float4){1, 1, 6, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 1, "addition result should be same");
	tuple3 = (t_float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "addition result should not be same");
}

Test(tuple_test, tuple_operation2)
{
	t_float4	tuple1;
	t_float4	tuple2;
	t_float4	tuple3;
	tuple1 = create_point(3, 2, 1);
	tuple2 = create_point(5, 6, 7);
	tuple1 = tuple1 - tuple2;
	tuple3 = create_vector(-2, -4, -6);
	cr_expect(same_tuple(tuple3, tuple1) == 1, "sub result should be same");
	tuple3 = (t_float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "sub result should not be same");
}

Test(tuple_test, tuple_operation3)
{
	t_float4	tuple1;
	t_float4	tuple2;
	t_float4	tuple3;
	tuple1 = create_point(3, 2, 1);
	tuple2 = create_vector(5, 6, 7);
	tuple1 = tuple1 - tuple2;
	tuple3 = create_point(-2, -4, -6);
	cr_expect(same_tuple(tuple3, tuple1) == 1, "sub result should be same");
	tuple3 = (t_float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "sub result should not be same");
}

Test(tuple_test, tuple_operation4)
{
	t_float4	tuple1;
	t_float4	tuple2;
	t_float4	tuple3;
	tuple1 = create_vector(3, 2, 1);
	tuple2 = create_vector(5, 6, 7);
	tuple1 = tuple1 - tuple2;
	tuple3 = create_vector(-2, -4, -6);
	cr_expect(same_tuple(tuple3, tuple1) == 1, "sub result should be same");
	tuple3 = (t_float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "sub result should not be same");
}

Test(tuple_test, opposite)
{
	t_float4 tup1 = create_vector(1, -2, 3);
	t_float4 tup2 = create_vector(0, 0, 0);
	cr_expect(same_tuple(tup1, tup2) == 0);
	tup1 = tup2 - tup1;
	t_float4	tup3 = create_vector(-1, 2, -3);
	cr_expect(same_tuple(tup1, tup3) == 1);
}

Test(tuple_test, opposite2)
{
	t_float4 tup1 = create_vector(1, -2, 3);
	t_float4 tup2 = create_vector(0, 0, 0);
	cr_expect(same_tuple(tup1, tup2) == 0);
	tup1 = (t_float4){0, 0, 0, 0}	- tup1;
	t_float4	tup3 = create_vector(-1, 2, -3);
	cr_expect(same_tuple(tup1, tup3) == 1);
}

/*negation of tuple is an implicite action of Clang,
no need for opposite(tuple) functon*/
Test(tuple_test, opposite3)
{
	t_float4 tup1 = create_vector(1, -2, 3);
	t_float4 tup2 = create_vector(0, 0, 0);
	cr_expect(same_tuple(tup1, tup2) == 0);
	tup1 = -tup1;
	t_float4	tup3 = create_vector(-1, 2, -3);
	cr_expect(same_tuple(tup1, tup3) == 1);
}

/*sclar multiplication and divison of tuples are implicit functions of clang*/
Test(tuple_test, scalar_mult)
{
	t_float4	tuple1 = (t_float4){1, -2, 3, -4};
	t_float4	tuple2 = (t_float4){3.5, -7, 10.5, -14};
	cr_expect(same_tuple(tuple1, tuple2) == 0);
	tuple1 *= 3.5;
	cr_expect(same_tuple(tuple1, tuple2) == 1);
	tuple1 = (t_float4){1, -2, 3, -4};
	tuple2 = (t_float4){0.5, -1, 1.5, -2};
	cr_expect(same_tuple(tuple1, tuple2) == 0);
	tuple1 *= 0.5;
	cr_expect(same_tuple(tuple1, tuple2) == 1);
}

Test(tuple_test, scalar_div)
{
	t_float4	tuple1 = (t_float4){1, -2, 3, -4};
	t_float4	tuple2 = (t_float4){0.5, -1, 1.5, -2};
	cr_expect(same_tuple(tuple1, tuple2) == 0);
	tuple1 /= 2;
	cr_expect(same_tuple(tuple1, tuple2) == 1);
}

// float addition_of_squared_elements(t_float4 vector)
// {
// 	return ((vector.x * vector.x) \
// 		+ (vector.y * vector.y) \
// 		+ (vector.z * vector.z) \
// 		+ (vector.w * vector.w));
// }

// float length(t_float4 vector)
// {
// 	float res;

// 	res = sqrt(addition_of_squared_elements(vector));
// 	return (res);
// }

// bool	same_float(float f1, float f2)
// {
// 	if (fabs(f1 - f2) > EPSILON)
// 		return (0);
// 	return (1);
// }

//magnitude is same thing as length of a vector
Test(tuple_test, magnitude)
{
	t_float4	tuple1 = create_vector(1, 0, 0);
	cr_expect(length(tuple1) == 1);
	tuple1 = create_vector(0, 1, 0);
	cr_expect(length(tuple1) == 1);
	tuple1 = create_vector(0, 0, 1);
	cr_expect(length(tuple1) == 1);
	tuple1 = create_vector(1, 2, 3);
	cr_expect(same_float(length(tuple1), sqrt(14.0)) == 1);
	tuple1 = create_vector(-1, -2, -3);
	cr_expect(same_float(length(tuple1), sqrt(14.0)) == 1);
}

// t_float4	normalize(t_float4 vector)
// {
// 	t_float4	res;

// 	res = vector / length(vector);
// 	return (res);
// }

Test(tuple_test, normalize1)
{
	t_float4 v = create_vector(4, 0, 0);
	t_float4 w = create_vector(1, 0, 0);
	t_float4	res;
	res = normalize(v);

	cr_expect(same_tuple(res, w) == 1);
}

Test(tuple_test, normalize2)
{
	t_float4 v = create_vector(1, 2, 3);
	t_float4 w = create_vector(0.26726, 0.53452, 0.80178);

	v = normalize(v);

	cr_expect(same_tuple(v, w) == 1);
}

Test(tuple_test, normalize3)
{
	t_float4 v = create_vector(1, 2, 3);
	t_float4 w;
	w = normalize(v);

	cr_expect(same_float(1, length(w)) == 1);
}

// float	dot_product(t_float4 tup1, t_float4 tup2)
// {
// 	return ((tup1.x * tup2.x) \
// 		+ (tup1.y * tup2.y) \
// 		+ (tup1.z * tup2.z) \
// 		+ (tup1.w * tup2.w));
// }

// t_float4	cross_product(t_float4 tup1, t_float4 tup2)
// {
// 	t_float4	res;

// 	res.x = tup1.y * tup2.z - tup1.z * tup2.y;
// 	res.y = tup1.z * tup2.x - tup1.x * tup2.z;
// 	res.z = tup1.x * tup2.y - tup1.y * tup2.x;
// 	res.w = 0;
// 	return (res);
// }

void	print_tuple(t_float4 var);
// float	dot(t_float4 un, t_float4 deux);

// t_float4	cross(t_float4 un, t_float4 deux);

Test(tuple_test, dot_prod)
{
	t_float4 v = create_vector(1, 2, 3);
	t_float4 v2 = create_vector(2, 3, 4);

	float v3 = dot_product(v, v2);
	cr_expect (same_float(v3, 20));

	// float test = dot(v, v2);
	// cr_expect (same_float(test, 20));
}

/*implicit multiplication of tuple only multiply v.x * v2.x, v.y * v.2y etc.
not useful for miniRT requirement*/
Test(tuple_test, cross_product)
{
	t_float4 v = create_vector(1, 2, 3);
	t_float4 v2 = create_vector(2, 3, 4);
	t_float4 v3 = create_vector(-1, 2, -1);
	t_float4 v4 = create_vector(1, -2, 1);
	cr_expect(same_tuple(cross_product(v, v2), v3) == 1);
	cr_expect(same_tuple(cross_product(v2, v), v4) == 1);
	// t_float4	test = v * v2;
	// print_tuple (test);
	// test = cross(v, v2);
	// print_tuple (test);
}
