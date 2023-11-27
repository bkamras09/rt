#ifndef PAINTH
#define PAINTH

#include "ray.h"
#include "object.h"

bool hit(ray r, float t_min, float t_max, Object *o);
Vec3 color(ray r, World *w);

#endif
