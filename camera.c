#include "vec3.h"
#include "ray.h"
#include "config.h"
#include "camera.h"
#include <math.h>


Vec3 random_in_unit_disk()
{
	Vec3 p;

	do {
		p = sub_Vec3(mul_scalar(make_Vec3(drand48(), drand48(), 0), 2.0), make_Vec3(1, 1, 0));
		//p = 2.0 * Vec3(drand48(), drand48(), 0) - make_Vec3(1, 1, 0);
	} while( dot( p, p ) >= 1.0 );

	return p;
}

Camera make_Camera(Vec3 look_from, Vec3 look_at, Vec3 vup, float vfov, float aperture)
{
    Camera c;
	c.lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = ASPECT_RATIO * half_height;

    c.aspect = ASPECT_RATIO;
    c.origin = look_from;
	c.aperture = aperture;
	c.focus_dist = Vec3_length( sub_Vec3(look_from, look_at) );
	c.vfov = vfov;
	c.vup = vup;
    c.w = unit_vector(sub_Vec3(look_from, look_at));
    c.u = unit_vector(cross(vup, c.w));
    c.v = cross(c.w, c.u);

    c.lower_left_corner = sub_Vec3(
        sub_Vec3(
            sub_Vec3(c.origin, mul_scalar(c.u, half_width * c.focus_dist)),
            mul_scalar(c.v, half_height * c.focus_dist)),
        mul_scalar(c.w, c.focus_dist));

    c.horizontal = mul_scalar(c.u, 2.0 * half_width * c.focus_dist);
    c.vertical = mul_scalar(c.v, 2.0 * half_height * c.focus_dist);

    return c;
}

ray get_ray(float s, float t, Camera c)
{
    Vec3 rd = mul_scalar(random_in_unit_disk(), c.lens_radius);
    Vec3 offset = add_Vec3(mul_scalar(c.u, rd.e[0]), mul_scalar(c.v, rd.e[1]));
	//  u * rd.x() +  * rd.y();

    Vec3 direction = add_Vec3(c.lower_left_corner, 
                              add_Vec3(mul_scalar(c.horizontal, s), 
                                       mul_scalar(c.vertical, t)));
    direction = sub_Vec3(direction, c.origin);
    direction = sub_Vec3(direction, offset);

    return make_ray(add_Vec3(c.origin, offset), direction);
}