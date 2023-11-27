#include "object.h"
#include "ray.h"

Object make_Object(float t, float radius, Vec3 p, Vec3 normal, Vec3 position) {
	Object o;
	o.t = t;
	o.p = p;
	o.normal = normal;
	o.position = position;
	o.radius = radius;
	return o;
}
