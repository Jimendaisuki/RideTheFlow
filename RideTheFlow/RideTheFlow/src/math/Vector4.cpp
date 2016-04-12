#include "Vector4.h"
#include <sstream>

Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);
Vector4 Vector4::One = Vector4(1, 1, 1, 1);

Vector4::Vector4()
: x(0), y(0), z(0), w(0)
{

}

Vector4::Vector4(float x, float y, float z, float w)
: x(x), y(y), z(z), w(w)
{

}

Vector4::Vector4(float s)
: x(s), y(s), z(s), w(s)
{

}

Vector4::Vector4(int x, int y, int z, int w)
: x((float)x), y((float)y), z((float)z), w((float)w)
{

}

Vector4::Vector4(int s)
: x((float)s), y((float)s), z((float)s), w((float)s)
{

}

Vector4::Vector4(const Vector4& vector)
: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{

}

Vector4& Vector4::operator = (const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

Vector4::operator std::string() const
{
	std::stringstream ss;
	ss << "(" << x << "," << y << "," << z << " )";
	return ss.str();
}

Vector4 operator + (const Vector4& v1, const Vector4& v2)
{
	Vector4 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w + v2.w;
	return result;
}

Vector4& operator += (Vector4& v1, const Vector4& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}

Vector4 operator - (const Vector4& v1, const Vector4& v2)
{
	Vector4 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return result;
}

Vector4& operator -= (Vector4& v1, const Vector4& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}

Vector4 operator * (const Vector4& v, const float f)
{
	Vector4 result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	result.w = v.w * f;
	return result;
}

Vector4 operator * (const float f, const Vector4& v)
{
	Vector4 result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	result.w = v.w * f;
	return result;
}

Vector4 operator * (const Vector4& v1, const Vector4& v2)
{
	Vector4 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	result.w = v1.w * v2.w;
	return result;
}

Vector4& operator *= (Vector4& v, const float f)
{
	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	v.w = v.w * f;
	return v;
}

Vector4& operator *= (const float f, Vector4& v)
{
	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	v.w = v.w * f;
	return v;
}

Vector4 operator / (const Vector4& v, const float f)
{
	Vector4 result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	result.w = v.w / f;
	return result;
}

Vector4 operator / (const float f, const Vector4& v)
{
	Vector4 result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	result.w = v.w / f;
	return result;
}

Vector4 operator / (const Vector4& v1, const  Vector4& v2)
{
	Vector4 result;
	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	result.w = v1.w / v2.w;
	return result;
}

Vector4& operator /= (Vector4& v, const float f)
{
	v.x = v.x / f;
	v.y = v.y / f;
	v.z = v.z / f;
	v.w = v.w / f;
	return v;
}

Vector4 operator - (Vector4& v)
{
	Vector4 result = v;
	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	result.w = -v.w;
	return result;
}