#ifndef RAYH
#define RAYH

#include "vec3.h"

typedef struct {
	Vec3 origin;
	Vec3 direction;
} ray;

Vec3 pt_at_param(ray r, float t);
ray make_ray(Vec3 origin, Vec3 direction);
float hit_Object(Vec3 center, float radius, ray r);

#endif
