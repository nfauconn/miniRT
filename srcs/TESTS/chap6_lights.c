#include "/mnt/nfs/homes/nfauconn/miniRT/includes/minirt.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/lights.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/ray.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/tuple.h"
#include "/mnt/nfs/homes/nfauconn/miniRT/includes/matrix.h"
#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"

//	printf("normal = {%f, %f, %f, %f}\normal", normal.x, normal.y, normal.z, normal.w);

Test(lights, normal_1)
{
	t_elem		sp;
	t_vector	normal;

	init_sphere(&sp);

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

	init_sphere(&sp);
	transfo_mx = translation(0, 1, 0);
	set_transform(&sp, transfo_mx);
	w_pt = create_point(0, 1.70711, -0.70711);
	w_normal = normal_atsphere(&sp, w_pt);
	cr_expect(same_tuple(w_normal, create_vector(0, 0.70711, -0.70711)));
}

Test(lights, normal_transformed_sp)
{
	t_elem		sp;
	t_point		w_pt;
	t_vector	w_normal;
	t_m4x4_f	transfo_mx;

	init_sphere(&sp);
	transfo_mx = scaling(1, 0.5, 1) * rotation_z(M_PI/5);
	set_transform(&sp, transfo_mx);
	w_pt = create_point(0, sqrt(2)/2, -sqrt(2)/2);
	w_normal = normal_atsphere(&sp, w_pt);
	cr_expect(same_tuple(w_normal, create_vector(0, 0.97014, -0.24254)));
}

/* Reflecting a vector approaching the normal at 45° */
Test(lights, find_reflecting_vector)
{
	t_vector	v;
	t_vector	n;
	t_vector	r;

	v = create_vector(1, -1, 0);
	n = create_vector(0, 1, 0);
	r = reflect(v, n);
	cr_expect(same_tuple(r, create_vector(1, 1, 0)));

	v = create_vector(0, -1, 0);
	n = create_vector(sqrt(2)/2, sqrt(2)/2, 0);
	r = reflect(v, n);
	cr_expect(same_tuple(r, create_vector(1, 0, 0)));
}

Test(lights, get_lighting)
{
	t_vector	eyev;
	t_vector	normalv;
	t_elem		light;
	t_rgb		res;
	t_point		position;

	light.material = default_material(&light);
	position = create_point(0, 0, 0); /* W_POS OU O_POS ???*/

/*	lighting with the eye btw the light and the surface, eye offset 90° (perpendicular to surface) */
	eyev = create_vector(0, 0, -1);
	normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 0, -10), create_color(1, 1, 1));
	res = lighting(light.material, &light, position, eyev, normalv);
	cr_expect(same_tuple(res, create_color(1.9, 1.9, 1.9)));

/*	lighting with the eye btw light & surface, eye offset 45°*/
	eyev = create_vector(0, sqrt(2)/2, -sqrt(2)/2);
	normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 0, -10), create_color(1, 1, 1));
	res = lighting(light.material, &light, position, eyev, normalv);
	cr_expect(same_tuple(res, create_color(1.0, 1.0, 1.0)));

/*	lighting with eye offset 90° , light offset 45°*/
	eyev = create_vector(0, 0, -1);
	normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 10, -10), create_color(1, 1, 1));
	res = lighting(light.material, &light, position, eyev, normalv);
	cr_expect(same_tuple(res, create_color(0.7364, 0.7364, 0.7364)));

/*	lighting with the eye in the path of the reflection vector */
	eyev = create_vector(0, -sqrt(2)/2, -sqrt(2)/2);
	normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 10, -10), create_color(1, 1, 1));
	res = lighting(light.material, &light, position, eyev, normalv);
//	printf("lighting = {%f, %f, %f, %f}\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(res, create_color(1.636385, 1.636385, 1.636385)));

/*	lighting with the light behind the surface and light beyond */
	eyev = create_vector(0, 0, -1);
	normalv = create_vector(0, 0, -1);
	point_light(&light, create_point(0, 0, 10), create_color(1, 1, 1));
	res = lighting(light.material, &light, position, eyev, normalv);
	cr_expect(same_tuple(res, create_color(0.1, 0.1, 0.1)));
}