#include <stdbool.h>
#include <math.h>
#include "vec3.h"
#include "ray.h"

Vec3 pt_at_param(ray r, float t) {
	return add_Vec3( r.origin, mul_scalar(r.direction, t) );
}

ray make_ray(Vec3 origin, Vec3 direction) {
	ray r;
	r.origin = origin;
	r.direction = direction;

	return r;
}
