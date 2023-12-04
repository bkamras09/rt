#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include "paint.h"
#include "material.h"

bool hit(ray r, float t_min, float t_max, Object *o)
{
	Vec3 oc = sub_Vec3(r.origin, o->position);
	float a = dot(r.direction, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - o->radius * o->radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			o->t = temp;
			o->p = pt_at_param(r, o->t);
			o->normal = div_scalar(sub_Vec3(o->p, o->position), o->radius);
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			o->t = temp;
			o->p = pt_at_param(r, o->t);
			o->normal = div_scalar(sub_Vec3(o->p, o->position), o->radius);
			return true;
		}
	}
	return false;
}

bool hit_any_Objects(ray r, float t_min, float t_max, Object *o, World *w)
{
	bool hit_anything = false;
	float closest_so_far = t_max;

	// it's a brute force max finding algorithm for the closest object to the camera
	for (unsigned int i = 0; i < w->number_of_objects; i++)
	{
		if (hit(r, t_min, closest_so_far, &w->objects[i]))
		{
			hit_anything = true;
			closest_so_far = w->objects[i].t;
			*o = w->objects[i];
		}
	}

	return hit_anything;
}

bool bounce(ray r, Object *o, Vec3 *attenuation, ray *scattered)
{
	switch (o->type)
	{
	case LAMBERTIAN:
		return scatter_LAMBERTIAN(r, o, attenuation, scattered);
	case METAL:
		return scatter_METAL(r, o, attenuation, scattered);
	case DIELECTRIC:
		return scatter_DIELECTRIC(r, o, attenuation, scattered);
	default:
		return false;
	}
}

bool scatter_METAL(ray r, Object *o, Vec3 *attenuation, ray *scattered)
{
	Vec3 reflected = reflect(unit_vector(r.direction), o->normal);
	*scattered = make_ray( o->p, add_Vec3( reflected, mul_scalar( random_in_unit_sphere(), o->fuzz ) ) ); //make_ray(o->p, reflected);
	*attenuation = o->albedo;
	return (dot(scattered->direction, o->normal) > 0);
}

bool scatter_LAMBERTIAN(ray r, Object *o, Vec3 *attenuation, ray *scattered)
{
	Vec3 target = add_Vec3(add_Vec3(o->p, o->normal), random_in_unit_sphere());
	*scattered = make_ray(o->p, sub_Vec3(target, o->p));
	*attenuation = o->albedo;
	return true;
}

bool scatter_DIELECTRIC(ray r, Object *o, Vec3 *attenuation, ray *scattered)
{
	Vec3 outward_normal;
	Vec3 reflected = reflect(r.direction, o->normal);
	float ni_over_nt;
	*attenuation = make_Vec3(1.0, 1.0, 1.0);
	Vec3 refracted;
	float reflect_prob;
	float cosine;
	if (dot(r.direction, o->normal) > 0)
	{
		outward_normal = mul_scalar(o->normal, -1.0);
		ni_over_nt = o->refractive_index;
		cosine = o->refractive_index * dot(r.direction, o->normal) / Vec3_length(r.direction);
	}
	else
	{
		outward_normal = o->normal;
		ni_over_nt = 1.0 / o->refractive_index;
		cosine = -dot(r.direction, o->normal) / Vec3_length(r.direction);
	}
	if (refract(r.direction, outward_normal, ni_over_nt, &refracted))
	{
		reflect_prob = schlick(cosine, o->refractive_index);
	}
	else
	{
		reflect_prob = 1.0;
	}
	if (drand48() < reflect_prob)
	{
		*scattered = make_ray(o->p, reflected);
	}
	else
	{
		*scattered = make_ray(o->p, refracted);
	}
	return true;
}

bool refract(Vec3 v, Vec3 n, float ni_over_nt, Vec3 *refracted)
{
	Vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0)
	{
		*refracted = sub_Vec3(mul_scalar(sub_Vec3(uv, mul_scalar(n, dt)), ni_over_nt), mul_scalar(n, sqrt(discriminant)));
		return true;
	}
	else
	{
		return false;
	}
}

float schlick(float cosine, float refractive_index)
{
	float r0 = (1 - refractive_index) / (1 + refractive_index);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

inline Vec3 color(ray r, World *w, int depth)
{
	Object o;
	ray scattered = make_ray(make_Vec3(0, 0, 0), make_Vec3(0, 0, 0));
	Vec3 attenuation = make_Vec3(0, 0, 0);
	if (hit_any_Objects(r, 0.001, FLT_MAX, &o, w))
	{
		if (depth < 50 && bounce(r, &o, &attenuation, &scattered))
		{
			return mul_Vec3(attenuation, color(scattered, w, depth + 1));
		}
		else
		{
			return make_Vec3(0, 0, 0);
		}
	}
	else
	{
		Vec3 unit_direction = unit_vector(r.direction);
		float t = 0.5 * (unit_direction.e[1] + 1.0);
		return add_Vec3(mul_scalar(make_Vec3(1.0, 1.0, 1.0), (1.0 - t)), mul_scalar(make_Vec3(0.5, 0.7, 1.0), t));
	}
}
