#ifndef MATERIALH
#define MATERIALH

#include <stdbool.h>
#include "ray.h"
#include "vec3.h"

typedef enum
{
	METAL = 0,
	DIELECTRIC,
	LAMBERTIAN
} EMaterialType;

typedef struct
{
	EMaterialType type;
	Vec3 albedo;
} Material;

#endif
