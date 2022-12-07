#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"
# include <math.h>
# include <stdio.h>
# include <errno.h>

typedef float float4 __attribute__((ext_vector_type(4)));
typedef int	int4 __attribute__((ext_vector_type(4)));

int is_equal(float x, float y)
{
	if (x == y)
		return (1);
	return (0);
}

bool	is_point(float4 tuple)
{
	if (tuple.w == 1.0)
		return (1);
	return(0);
}

bool	is_vector(float4 tuple)
{
	if (tuple.w == 1.0)
		return (0);
	return(1);
}



bool	same_tuple(float4 tup1, float4 tup2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(tup1.x - tup2.x) > epsilon || fabs(tup1.y - tup2.y) > epsilon
		|| fabs(tup1.z - tup2.z) > epsilon || fabs(tup1.w - tup2.w) > epsilon)
		return (0);
	return (1);
}

bool	tuple_bool(int4 tuple)
{
	if(tuple.x == 0 || tuple.y == 0 || tuple.z == 0 || tuple.w == 0)
		return (0);
	return (1);
}

Test (tuple_test, tuple_point)
{
	float4	tuple1 = (float4){4.3, -4.2, 3.1, 1.0};
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
	float4	tuple2 = (float4){4.3, -4.2, 3.1, 0.0};
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
	float4	tuple1 = (float4){4, -4, 3, 1.0};
	float4	tuple2;
	tuple2 = create_point(4, -4, 3);
	cr_expect(same_tuple(tuple1, tuple2) == 1, "create point");
	tuple1 = (float4){4, 4, 3, 1.0};
	cr_expect(same_tuple(tuple1, tuple2) == 0, "create point");
	tuple1 = (float4){4, -4, 3, 0.0};
	float4	tuple3;
	tuple3 = create_vector(4, -4, 3);
	cr_expect(same_tuple(tuple1, tuple3) == 1, "create vector");
	tuple1 = (float4){4, 4, 3, 1.0};
	cr_expect(same_tuple(tuple1, tuple3) == 0, "create vector");

	int4 fun;
	fun = tuple1 == tuple3;
	cr_expect(tuple_bool(fun) == 0, "compare vector should fail");
	tuple1 = (float4){4, -4, 3, 0.0};
	fun = tuple1 == tuple3;
	cr_expect(tuple_bool(fun) == 1, "compare vector should succeed");
	// printf ("%d %d %d %d\n", fun.s0, fun.s1,fun.s2,fun.s3);
}

Test(tuple_test, tuple_operation)
{
	float4	tuple1;
	float4	tuple2;
	float4	tuple3;
	tuple1 = create_point(3, -2, 5);
	tuple2 = create_vector(-2, 3, 1);
	tuple1 = tuple1 + tuple2;
	tuple3 = (float4){1, 1, 6, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 1, "addition result should be same");
	tuple3 = (float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "addition result should not be same");
}

Test(tuple_test, tuple_operation2)
{
	float4	tuple1;
	float4	tuple2;
	float4	tuple3;
	tuple1 = create_point(3, 2, 1);
	tuple2 = create_point(5, 6, 7);
	tuple1 = tuple1 - tuple2;
	tuple3 = create_vector(-2, -4, -6);
	cr_expect(same_tuple(tuple3, tuple1) == 1, "sub result should be same");
	tuple3 = (float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "sub result should not be same");
}

Test(tuple_test, tuple_operation3)
{
	float4	tuple1;
	float4	tuple2;
	float4	tuple3;
	tuple1 = create_point(3, 2, 1);
	tuple2 = create_vector(5, 6, 7);
	tuple1 = tuple1 - tuple2;
	tuple3 = create_point(-2, -4, -6);
	cr_expect(same_tuple(tuple3, tuple1) == 1, "sub result should be same");
	tuple3 = (float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "sub result should not be same");
}

Test(tuple_test, tuple_operation4)
{
	float4	tuple1;
	float4	tuple2;
	float4	tuple3;
	tuple1 = create_vector(3, 2, 1);
	tuple2 = create_vector(5, 6, 7);
	tuple1 = tuple1 - tuple2;
	tuple3 = create_vector(-2, -4, -6);
	cr_expect(same_tuple(tuple3, tuple1) == 1, "sub result should be same");
	tuple3 = (float4){1, 1, 5, 1};
	cr_expect(same_tuple(tuple3, tuple1) == 0, "sub result should not be same");
}

Test(tuple_test, opposite)
{
	float4 tup1 = create_vector(1, -2, 3);
	float4 tup2 = create_vector(0, 0, 0);
	cr_expect(same_tuple(tup1, tup2) == 0);
	tup1 = tup2 - tup1;
	float4	tup3 = create_vector(-1, 2, -3);
	cr_expect(same_tuple(tup1, tup3) == 1);
}
Test(tuple_test, opposite2)
{
	float4 tup1 = create_vector(1, -2, 3);
	float4 tup2 = create_vector(0, 0, 0);
	cr_expect(same_tuple(tup1, tup2) == 0);
	tup1 = (float4){0, 0, 0, 0}	- tup1;
	float4	tup3 = create_vector(-1, 2, -3);
	cr_expect(same_tuple(tup1, tup3) == 1);
}

Test(tuple_test, scalar_mult)
{
	float4	tuple1 = (float4){1, -2, 3, -4};
	float4	tuple2 = (float4){3.5, -7, 10.5, -14};
	cr_expect(same_tuple(tuple1, tuple2) == 0);
	tuple1 *= 3.5;
	cr_expect(same_tuple(tuple1, tuple2) == 1);
	tuple1 = (float4){1, -2, 3, -4};
	tuple2 = (float4){0.5, -1, 1.5, -2};
	cr_expect(same_tuple(tuple1, tuple2) == 0);
	tuple1 *= 0.5;
	cr_expect(same_tuple(tuple1, tuple2) == 1);
}

Test(tuple_test, scalar_div)
{
	float4	tuple1 = (float4){1, -2, 3, -4};
	float4	tuple2 = (float4){0.5, -1, 1.5, -2};
	cr_expect(same_tuple(tuple1, tuple2) == 0);
	tuple1 /= 2;
	cr_expect(same_tuple(tuple1, tuple2) == 1);
}

float addition_of_squared_elements(float4 vector)
{
	return ((vector.x * vector.x) \
		+ (vector.y * vector.y) \
		+ (vector.z * vector.z) \
		+ (vector.w * vector.w));
}

float length(float4 vector)
{
	float res;

	res = sqrt(addition_of_squared_elements(vector));
	return (res);
}

bool	same_float(float f1, float f2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(f1 - f2) > epsilon)
		return (0);
	return (1);
}

//same as length
Test(tuple_test, magnitude)
{
	float4	tuple1 = create_vector(1, 0, 0);
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

float4	normalize(float4 vector)
{
	float4	res;

	res = vector / length(vector);
	return (res);
}

Test(tuple_test, normalize1)
{
	float4 v = create_vector(4, 0, 0);
	float4 w = create_vector(1, 0, 0);
	float4	res;
	res = normalize(v);

	cr_expect(same_tuple(res, w) == 1);
}

Test(tuple_test, normalize2)
{
	float4 v = create_vector(1, 2, 3);
	float4 w = create_vector(0.26726, 0.53452, 0.80178);

	v = normalize(v);

	cr_expect(same_tuple(v, w) == 1);
}

Test(tuple_test, normalize3)
{
	float4 v = create_vector(1, 2, 3);
	float4 w;
	w = normalize(v);

	cr_expect(same_float(1, length(w)) == 1);
}

float	dot_product(float4 tup1, float4 tup2)
{
	return ((tup1.x * tup2.x) \
		+ (tup1.y * tup2.y) \
		+ (tup1.z * tup2.z) \
		+ (tup1.w * tup2.w));
}

float4	cross_product(float4 tup1, float4 tup2)
{
	float4	res;

	res.x = tup1.y * tup2.z - tup1.z * tup2.y;
	res.y = tup1.z * tup2.x - tup1.x * tup2.z;
	res.z = tup1.x * tup2.y - tup1.y * tup2.x;
	res.w = 0;
	return (res);
}

Test(tuple_test, cross_product)
{
	float4 v = create_vector(1, 2, 3);
	float4 v2 = create_vector(2, 3, 4);
	float4 v3 = create_vector(-1, 2, -1);
	float4 v4 = create_vector(1, -2, 1);
	cr_expect(same_tuple(cross_product(v, v2), v3) == 1);
	cr_expect(same_tuple(cross_product(v2, v), v4) == 1);
}
// Test (tuple_test, test1)
// {
// 	cr_expect(ft_isalnum('a') == 1, "\'a\' est alphanumerique");
// }