#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include "paint.h"
#include "material.h"

bool hit(ray r, float t_min, float t_max, Object *o) {
	Vec3 oc = sub_Vec3(r.origin, o->position); 
	float a = dot(r.direction, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - o->radius*o->radius;
	float discriminant = b*b - a*c;
	
	if ( discriminant > 0 ) {
		float temp = ( -b - sqrt(b*b - a*c)) / a;
		if ( temp < t_max && temp > t_min) {
			o->t = temp;
			o->p = pt_at_param(r, o->t);
			o->normal = div_scalar( sub_Vec3( o->p, o->position), o->radius );
			return true;
		}
		temp = ( -b + sqrt(b*b - a*c)) / a;
		if ( temp < t_max && temp > t_min ) {
			o->t = temp;
			o->p = pt_at_param(r, o->t);
			o->normal =  div_scalar( sub_Vec3( o->p, o->position), o->radius );
			return true;
		}
	}
	return false;
}

bool hit_any_Objects(ray r, float t_min, float t_max, Object *o, World *w) {
	bool hit_anything = false;
	float closest_so_far = t_max;
	
	// it's a brute force max finding algorithm for the closest object to the camera
	for (unsigned int i = 0; i < w->object_limit; i++) {
		if ( hit( r, t_min, closest_so_far, &w->objects[i] ) ) {
			hit_anything = true;
			closest_so_far = w->objects[i].t;
			*o = w->objects[i];
		}
	}

	return hit_anything;
}

inline Vec3 color(ray r, World *w) {
	Object o;
	if (hit_any_Objects(r, 0.001, FLT_MAX, &o, w)) {
		//Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		Vec3 target = add_Vec3( add_Vec3( o.p, o.normal ), random_in_unit_sphere() );
		//return 0.5 * color( ray(rec.p, target - rec.p), world);
		return mul_scalar( (color( make_ray( o.p, sub_Vec3( target, o.p ) ) , w)  ), 0.5 );
	} else {
		Vec3 unit_direction = unit_vector(r.direction);
		float t = 0.5 * (unit_direction.e[1] + 1.0);
		return add_Vec3( mul_scalar( make_Vec3( 1.0, 1.0, 1.0), (1.0 - t) ), mul_scalar( make_Vec3( 0.5, 0.7, 1.0 ), t ) );	
	}
}
