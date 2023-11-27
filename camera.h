#ifndef CAMERAH
#define CAMERAH

#include "vec3.h"
#include "ray.h"
#include "config.h"

typedef struct {
	Vec3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 origin;
} Camera;

Camera make_Camera() {
	Camera c;

	c.lower_left_corner = make_Vec3(-2.0, -1.0, -1.0);
	c.horizontal = make_Vec3(4.0, 0.0, 0.0);
	c.vertical =  make_Vec3(0.0, 2.0, 0.0);
	c.origin = make_Vec3(0.0, 0.0, 0.0);

	return c;
}

ray get_ray(float u, float v, Camera c) {
	return make_ray(c.origin, add_Vec3(add_Vec3(c.lower_left_corner, mul_scalar(c.horizontal, u)), mul_scalar(c.vertical, v)));
}

#endif
