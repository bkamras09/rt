#include <stdio.h>
#include "object.h"
#include "ray.h"
#include "config.h"


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

Object new_metal(Vec3 position, Vec3 albedo, float radius, float fuzz)
{
	Object o = new_Object(radius, position, METAL);
	o.albedo = albedo;
	o.fuzz = fuzz;
	o.refractive_index = -1;

	return o;
}

Object new_lambertian(Vec3 position, Vec3 albedo, float radius)
{
	Object o = new_Object(radius, position, LAMBERTIAN);
	o.albedo = albedo;
	o.refractive_index = -1;
	o.fuzz = -1;

	return o;
}

Object new_dielectric(Vec3 position, float radius, float refractive_index)
{
	Object o = new_Object(radius, position, DIELECTRIC);
	o.refractive_index = refractive_index;
	o.fuzz = -1;
	o.albedo = make_Vec3(-1, -1, -1);

	return o;
}

Object new_Object(float radius, Vec3 position, EMaterialType type)
{
	Object o;

	o.t = 0;
	o.p = make_Vec3(0, 0, 0);
	o.normal = make_Vec3(0, 0, 0);
	o.position = position;
	o.radius = radius;
	o.type = type;

	return o;
}

World create_empty_world()
{
	World w;
	w.number_of_objects = 0;
	w.object_limit = WORLD_OBJECT_LIMIT;

	return w;
}

void add_to_World(World *w, Object o)
{
	if (w->number_of_objects > w->object_limit) {
		printf("ERROR: Object limit has been reached.  Cannot add any more objects.\n");
	} else {
		w->objects[w->number_of_objects++] = o;
	}
}