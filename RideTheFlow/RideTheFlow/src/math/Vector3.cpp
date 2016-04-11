#include "Vector3.h"
#include <cmath>
#include "Vector3Utility.h"
Vector3 vector3(float x, float y, float z) {
	Vector3 result = { x, y, z };
	return result;
}
float RCVector3::dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vector3 RCVector3::cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
	
	return result;
}
float RCVector3::length(const Vector3& v) {
	return (float)std::sqrt(RCVector3::dot(v, v));
}
Vector3 RCVector3::normalize(const Vector3& v) {
	Vector3 result = v;
	float len = RCVector3::length(result);
	if (len != 0) {
		result /= len;
	}
	return result;
}
Vector3 operator + (const Vector3& v) {
	return v;
}
Vector3 operator - (const Vector3& v) {
	Vector3 result = { -v.x, -v.y, -v.z };
	return result;
}
Vector3& operator += (Vector3& v1, const Vector3& v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}
Vector3& operator -= (Vector3& v1, const Vector3& v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}
Vector3& operator *= (Vector3& v, float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}
Vector3& operator /= (Vector3& v, float s) {
	v *= 1.0f / s;
	return v;
}
Vector3 operator + (const Vector3& v1, const Vector3& v2) {
	Vector3 result = v1;
	return result += v2;
}
Vector3 operator - (const Vector3& v1, const Vector3& v2) {
	Vector3 result = v1;
	return result -= v2;
}
Vector3 operator * (const Vector3& v, float s) {
	Vector3 result = v;
	return result *= s;
}
Vector3 operator * (float s, const Vector3& v) {
	Vector3 result = v;
	return result *= s;
}
Vector3 operator / (const Vector3& v, float s) {
	Vector3 result = v;
	return result /= s;
}