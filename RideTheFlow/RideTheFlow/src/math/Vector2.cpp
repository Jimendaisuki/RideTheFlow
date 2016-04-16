#include "Vector2.h"
#include <cmath>
#include <sstream>
#include "Point.h"

Vector2 Vector2::Zero = Vector2(0, 0);
Vector2 Vector2::One = Vector2(1, 1);
Vector2 Vector2::Left = Vector2(-1, 0);
Vector2 Vector2::Right = Vector2(1, 0);
Vector2 Vector2::Up = Vector2(0, -1);
Vector2 Vector2::Down = Vector2(0, 1);

Vector2 Vector2::Center()
{
	int width, height;
	GetWindowSize(&width, &height);
	return Vector2(width / 2.0f, height / 2.0f);
}

Vector2::Vector2()
: x(0), y(0)
{

}

Vector2::Vector2(float x, float y)
: x(x), y(y)
{

}

Vector2::Vector2(int x, int y)
: x((float)x), y((float)y)
{

}

Vector2::Vector2(const Vector2& vec)
: x(vec.x), y(vec.y)
{

}

Vector2::Vector2(const VECTOR& vec)
: x(vec.x), y(vec.y)
{

}

Vector2::Vector2(float s)
: x(s), y(s)
{

}

Vector2::Vector2(int s)
: x((float)s), y((float)s)
{

}

float Vector2::Length() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::LengthPow2() const
{
	return x * x + y * y;
}

float Vector2::Distance(const Vector2& other) const
{
	return (other - *this).Length();
}

float Vector2::DistancePow2(const Vector2& other) const
{
	return (other - *this).LengthPow2();
}

void Vector2::Normalize()
{
	(*this) /= Length();
}

Vector2 Vector2::Normalized() const
{
	return Normalize(Vector2(x, y));
}

float Vector2::Dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::Inner(const Vector2& v) const
{
	Vector2 v1 = Vector2(x, y);
	Vector2 v2 = v;
	return acosf(v1.Normalized().Dot(v2.Normalized()));
}

Vector2 Vector2::Normalize(const Vector2& v)
{
	Vector2 result = v;
	result.Normalize();
	return result;
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2)
{
	return (v2 - v1).Length();
}

float Vector2::DistancePow2(const Vector2& v1, const Vector2& v2)
{
	return (v2 - v1).LengthPow2();
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Inner(const Vector2& v1, const Vector2& v2)
{
	Vector2 v1_ = v1;
	Vector2 v2_ = v2;
	return acosf(Dot(v1_.Normalized(), v2_.Normalized()));
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.y * v2.x - v1.x * v2.y;
}

// 二つのベクトル間の線形補間をする
Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, float amount)
{
	if (amount < 0.0f) {
		amount = 0.0f;
	}
	else if (amount > 1.0f) {
		amount = 1.0f;
	}
	return start * (1.0f - amount) + end * amount;
}

Point Vector2::ToPoint(const Vector2& v)
{
	Point result;
	result.x = (int)v.x;
	result.y = (int)v.y;
	return result;
}

Point Vector2::ToPoint() const
{
	return ToPoint(*this);
}

Vector2& Vector2::operator = (const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2::operator std::string() const
{
	std::stringstream ss;
	ss << "(" << x << "," << y << ")";
	return ss.str();
}

Vector2 operator + (const Vector2& v1, const Vector2& v2)
{
	Vector2 r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	return r;
}

Vector2& operator += (Vector2& v1, const Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2 operator - (const Vector2& v1, const Vector2& v2)
{
	Vector2 r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	return r;
}

Vector2& operator -= (Vector2& v1, const Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2 operator * (const Vector2& v, const float f)
{
	Vector2 r;
	r.x = v.x * f;
	r.y = v.y * f;
	return r;
}

Vector2 operator * (const float f, const Vector2& v)
{
	Vector2 r;
	r.x = v.x * f;
	r.y = v.y * f;
	return r;
}

Vector2& operator *= (Vector2& v, const float f)
{
	v.x *= f;
	v.y *= f;
	return v;
}

Vector2& operator *= (const float f, Vector2& v)
{
	v.x *= f;
	v.y *= f;
	return v;
}

Vector2 operator / (const Vector2& v, const float f)
{
	Vector2 r;
	r.x = v.x / f;
	r.y = v.y / f;
	return r;
}

Vector2 operator / (const float f, const Vector2& v)
{
	Vector2 r;
	r.x = v.x / f;
	r.y = v.y / f;
	return r;
}

Vector2& operator /= (Vector2& v, const float f)
{
	v.x /= f;
	v.y /= f;
	return v;
}

Vector2 operator - (const Vector2& v)
{
	Vector2 r = v;
	r.x = -r.x;
	r.y = -r.y;
	return r;
}
