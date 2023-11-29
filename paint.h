#ifndef PAINTH
#define PAINTH

#include "ray.h"
#include "object.h"

bool hit(ray r, float t_min, float t_max, Object *o);
Vec3 color(ray r, World *w, int depth);

bool bounce(ray r, Object *o, Vec3 *attenuation, ray *scattered);
bool scatter_METAL(ray r, Object *o, Vec3 *attenuation, ray *scattered);
bool scatter_LAMBERTIAN(ray r, Object *o, Vec3 *attenuation, ray *scattered);
bool scatter_DIELECTRIC(ray r, Object *o, Vec3 *attenuation, ray *scattered);
float schlick(float cosine, float refractive_index);
#endif
