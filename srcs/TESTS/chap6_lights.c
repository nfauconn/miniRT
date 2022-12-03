#include "/mnt/nfs/homes/nfauconn/miniRT/includes/minirt.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/lights.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/ray.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/tuple.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/matrix.h"
#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"

//	printf("normal = {%f, %f, %f, %f}\normal", normal.x, normal.y, normal.z, normal.w);

Test(lights, normal_1)
{
	t_elem		sp = init_sphere();
	t_vector	normal;

	normal = normal_atsphere(&sp, create_point(1, 0, 0));
	cr_expect(same_tuple(normal, create_vector(1, 0, 0)));

	normal = normal_atsphere(&sp, create_point(0, 1, 0));
	cr_expect(same_tuple(normal, create_vector(0, 1, 0)));

	normal = normal_atsphere(&sp, create_point(0, 0, 1));
	cr_expect(same_tuple(normal, create_vector(0, 0, 1)));

	normal = normal_atsphere(&sp, create_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
	cr_expect(same_tuple(normal, create_vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)));
}

Test(lights, normal_translated_sp)
{
	t_elem		sp;
	t_point		w_pt;
	t_vector	w_normal;
	t_m4x4_f	transfo_mx;

	sp = init_sphere();
	transfo_mx = translation(0, 1, 0);
	set_transform(&sp, transfo_mx);
	w_pt = create_point(0, sqrt(2)/2, -sqrt(2)/2);
	w_normal = normal_atsphere(&sp, w_pt);
	cr_expect(same_tuple(w_normal, create_vector(0, 0.70711, -0.70711)));
}

Test(lights, normal_transformed_sp)
{
	t_elem		sp;
	t_point		w_pt;
	t_vector	w_normal;
	t_m4x4_f	transfo_mx;

	sp = init_sphere();
	transfo_mx = scaling(1, 0.5, 1) * rotation_z(M_PI/5);
	set_transform(&sp, transfo_mx);
	w_pt = create_point(0, sqrt(2)/2, -sqrt(2)/2);
	w_normal = normal_atsphere(&sp, w_pt);
	cr_expect(same_tuple(w_normal, create_vector(0, 0.97014, -0.24254)));
}