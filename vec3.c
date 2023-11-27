#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vec3.h"

inline Vec3 make_Vec3(float e0, float e1, float e2) {
	Vec3 v; v.e[0] = e0; v.e[1] = e1; v.e[2] = e2; return v;
}
inline Vec3 negate_Vec3(Vec3 v) {
	v.e[0] = -v.e[0]; v.e[1] = -v.e[1]; v.e[2] = -v.e[2]; return v;
}
inline float Vec3_length(Vec3 v) {
	return (float)sqrt( v.e[0]*v.e[0]  +  v.e[1]*v.e[1]  +  v.e[2]*v.e[2] );
}
inline float Vec3_squared_length(Vec3 v) {
	return (float)(v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2]);
}
inline void make_unit_vector(Vec3 v) {
	float k = 1.0 / sqrt(v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2]);
	v.e[0] *= k; v.e[1] *= k; v.e[2] *= k;
}
inline Vec3 unit_vector(Vec3 v) {
	return div_scalar( v, Vec3_length(v) ); // v / v.length;
}
inline Vec3 random_in_unit_sphere() {
	Vec3 p;
	do {
		p = sub_Vec3(mul_scalar(make_Vec3(drand48(), drand48(), drand48()), 2.0), make_Vec3(1, 1, 1));
		//p = 2 * Vec3( drand48(), drand48(), drand48() ) - Vec3(1, 1, 1);
	} while (Vec3_squared_length(p) >= 1.0);

	return p;
}
inline Vec3 add_Vec3(Vec3 v1, Vec3 v2) {
	return make_Vec3((v1.e[0] + v2.e[0]), (v1.e[1] + v2.e[1]), (v1.e[2] + v2.e[2]));
}
inline Vec3 sub_Vec3(Vec3 v1, Vec3 v2) {
	return make_Vec3((v1.e[0] - v2.e[0]), (v1.e[1] - v2.e[1]), (v1.e[2] - v2.e[2]));
}
inline Vec3 mul_Vec3(Vec3 v1, Vec3 v2) {
	return make_Vec3( v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline Vec3 div_Vec3(Vec3 v1, Vec3 v2) {
	return make_Vec3( v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}



inline Vec3 add_inc_Vec3(Vec3 v1, Vec3 v2) {
 return make_Vec3(v1.e[0] += v2.e[0], v1.e[1] += v2.e[1], v1.e[2] += v2.e[2]);	
}
inline Vec3 div_dec_Vec3(Vec3 v, float t) {
	return make_Vec3(v.e[0] /= t, v.e[1] /= t, v.e[2] /= t);
}



inline Vec3 mul_scalar(Vec3 v, float t) {
	return make_Vec3( (v.e[0] * t), (v.e[1] * t), (v.e[2] * t) );
}
inline Vec3 div_scalar(Vec3 v, float t) {
	return make_Vec3( (v.e[0] / t), (v.e[1] / t), (v.e[2] / t) );
}
inline Vec3 sub_scalar(Vec3 v, float t) {
	return make_Vec3((v.e[0] - t), (v.e[1] - t), (v.e[2] - t));
}
inline float dot(Vec3 v1, Vec3 v2) {
	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}
inline Vec3 cross(Vec3 v1, Vec3 v2) {
	Vec3 v;
	v.e[0] =   v.e[1]*v.e[2] - v.e[2]*v.e[1];
	v.e[1] = -(v.e[0]*v.e[2] - v.e[2]*v.e[0]);
	v.e[2] =   v.e[0]*v.e[1] - v.e[1]*v.e[0];
	
	return v;
}
inline Vec3 reflect(Vec3 v, Vec3 n) {
	//return v - 2*dot(v, n)*n;
	return sub_Vec3( v, mul_scalar(n, ( 2 * dot( v, n ) ) ) );
	}
