#ifndef CAMERAH
#define CAMERAH

#include "vec3.h"
#include "ray.h"
#include "config.h"
#include <math.h>

typedef struct {
	Vec3 lower_left_corner,v, u, w, horizontal, vertical, origin, vup;
	float aspect, vfov, lens_radius, aperture, focus_dist;
} Camera;

Vec3 random_in_unit_disk();
Camera make_Camera(Vec3 look_from, Vec3 look_at, Vec3 vup, float vfov, float aperture);
Camera make_default_Camera();
ray get_ray(float s, float t, Camera c);

#endif
