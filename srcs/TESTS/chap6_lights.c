#include "/mnt/nfs/homes/nfauconn/miniRT/includes/minirt.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/lights.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/ray.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/tuple.h"
#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"

Test(lights, normal)
{
	t_elem		sphere = init_sphere();
	t_vector	vector;

	vector = normal_atsphere(sphere, create_point(1, 0, 0));
	cr_expect(same_tuple(vector, create_vector(1, 0, 0)));
	vector = normal_atsphere(sphere, create_point(0, 1, 0));
	cr_expect(same_tuple(vector, create_vector(0, 1, 0)));
	vector = normal_atsphere(sphere, create_point(0, 0, 1));
	cr_expect(same_tuple(vector, create_vector(0, 0, 1)));
	vector = normal_atsphere(sphere, create_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
	cr_expect(same_tuple(vector, create_vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)));
}

Test(lights, blabla)
{

}
//	printf("vector = {%f, %f, %f, %f}\n", vector.x, vector.y, vector.z, vector.w);