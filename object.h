#ifndef OBJECTH
#define OBJECTH

#include <stdbool.h>
#include <stdlib.h>
#include "ray.h"
#include "material.h"

typedef enum
{
	SPHERE = 0,
	OVOID,
	RECTANGULAR_PRISM,
	TRIANGULAR_PRISM,
	OCTAHEDRON,
	ICOSAHEDRON,
	DODECAHEDRON
} EShapes;

typedef struct
{
	float t;	  // time so we can do motion blur later
	float radius; // here this works for spheres, but eventually Object should allow for shapes and/or meshes
	Vec3 p;
	Vec3 normal;
	Vec3 position;
	EMaterialType type;
	Vec3 albedo;
	float refractive_index;
	// TODO: this is supposed to be a generic struct that stores object geometries.
	// How can I use this struct to store any arbitrary list of points?
} Object;

typedef struct
{
	unsigned int object_limit;
	Object objects[256];
} World;

Object make_Object(float t, float radius, Vec3 p, Vec3 normal, Vec3 position, Vec3 albedo, EMaterialType type);
bool scatter(ray r_in, Object o, Vec3 attenuation, ray scattered);
bool refract(Vec3 v, Vec3 n, float ni_over_nt, Vec3 *refracted);
#endif
