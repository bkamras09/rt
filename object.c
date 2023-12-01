#include "object.h"
#include "ray.h"

Object make_Object(float t, float radius, Vec3 position, Vec3 albedo, EMaterialType type)
{
	Object o;
	o.t = t;
	o.p = make_Vec3(0, 0, 0);
	o.normal = make_Vec3(0, 0, 0);
	o.position = position;
	o.radius = radius;
	o.albedo = albedo;
	o.type = type;
	return o;
}
