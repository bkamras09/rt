#ifndef VEC3H
#define VEC3H

typedef struct {
	float x;
	float y;
	float z;
	float e[3];
} Vec3;

Vec3 random_in_unit_sphere();
Vec3 div_Vec3(Vec3 v1, Vec3 v2);
Vec3 add_Vec3(Vec3 v1, Vec3 v2);
Vec3 sub_Vec3(Vec3 v1, Vec3 v2);

Vec3 div_dec_Vec3(Vec3 v, float t);
Vec3 add_inc_Vec3(Vec3 v1, Vec3 v2);

Vec3 div_scalar(Vec3 v, float t);
Vec3 mul_scalar(Vec3 v, float t);

Vec3 make_Vec3(float e0, float e1, float e2);
Vec3 negate_Vec3(Vec3 v);

float dot(Vec3 v1, Vec3 v2);
float Vec3_length(Vec3 v);
float Vec3_squared_length(Vec3 v);

Vec3 cross(Vec3 v1, Vec3 v2);
Vec3 unit_vector(Vec3 v);
Vec3 reflect(Vec3 v, Vec3 n);


#endif
