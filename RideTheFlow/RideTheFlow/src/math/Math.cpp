#include "Math.h"
#include <math.h>
#include <cassert>

// 角度を渡し、Sinを返す
float Math::Sin(float angle)
{
	return sinf(Radian(angle));
}

// 角度を渡し、Sinを返す
float Math::Sin(double angle)
{
	return sinf(Radian((float)angle));
}

// 角度を渡し、Sinを返す
float Math::Sin(int angle)
{
	return sinf(Radian((float)angle));
}

// 角度を渡し、Cosを返す
float Math::Cos(float angle)
{
	return cosf(Radian(angle));
}

// 角度を渡し、Cosを返す
float Math::Cos(double angle)
{
	return cosf(Radian((float)angle));
}

// 角度を渡し、Cosを返す
float Math::Cos(int angle)
{
	return cosf(Radian((float)angle));
}

// 角度を渡し、Tanを返す
float Math::Tan(float angle)
{
	return tanf(Radian(angle));
}

// 角度を渡し、Tanを返す
float Math::Tan(double angle)
{
	return tanf(Radian((float)angle));
}

// 角度を渡し、Tanを返す
float Math::Tan(int angle)
{
	return tanf(Radian((float)angle));
}

// 角度を渡し、逆正弦を返す
float Math::Asin(float angle)
{
	return asinf(Radian(angle));
}

// 角度を渡し、逆正弦を返す
float Math::Asin(double angle)
{
	return asinf(Radian((float)angle));
}

// 角度を渡し、逆正弦を返す
float Math::Asin(int angle)
{
	return asinf(Radian((float)angle));
}

// 角度を渡し、逆余弦を返す
float Math::Acos(float angle)
{
	return acosf(Radian(angle));
}

// 角度を渡し、逆余弦を返す
float Math::Acos(double angle)
{
	return acosf(Radian((float)angle));
}

// 角度を渡し、逆余弦を返す
float Math::Acos(int angle)
{
	return acosf(Radian((float)angle));
}

// 角度を渡し、逆正接を返す
float Math::Atan(float angle)
{
	return atanf(Radian(angle));
}

// 角度を渡し、逆正接を返す
float Math::Atan(double angle)
{
	return atanf(Radian((float)angle));
}

// 角度を渡し、逆正接を返す
float Math::Atan(int angle)
{
	return atanf(Radian((float)angle));
}

float Math::Atan(float y, float x)
{
	return atan2(y, x);
}

// y / x の逆正接を返す
float Math::Atan2(float y, float x)
{
	return atan2f(Radian(y), Radian(x));
}

// y / x の逆正接を返す
float Math::Atan2(double y, double x)
{
	return atan2f(Radian((float)y), Radian((float)x));
}

// y / x の逆正接を返す
float Math::Atan2(int y, int x)
{
	return atan2f(Radian((float)y), Radian((float)x));
}

// ラジアンを渡し、角度を返す
float Math::Degree(float radian)
{
	return radian / PI * 180.0f;
}

// 角度を渡し、ラジアンを返す
float Math::Radian(float degree)
{
	return degree * PI / 180.0f;
}

// 二つの実数を渡し、大きい方を返す
float Math::Max(float value1, float value2)
{
	return fmaxf(value1, value2);
}

// 二つの浮動小数点数を渡し、大きい方を返す
float Math::Max(double value1, double value2)
{
	return fmaxf((float)value1, (float)value2);
}

// 二つの整数を渡し、大きい方を返す
float Math::Max(int value1, int value2)
{
	return fmaxf((float)value1, (float)value2);
}

// 二つの実数を渡し、小さい方を返す
float Math::Min(float value1, float value2)
{
	return fminf(value1, value2);
}

// 二つの浮動小数点数を渡し、小さい方を返す
float Math::Min(double value1, double value2)
{
	return fminf((float)value1, (float)value2);
}

// 二つの整数を渡し、小さい方を返す
float Math::Min(int value1, int value2)
{
	return fminf((float)value1, (float)value2);
}

// 実数を渡し、べき乗を返す
float Math::Pow(float value, float power)
{
	return powf(value, power);
}

// 浮動小数点数を渡し、べき乗を返す
float Math::Pow(double value, float power)
{
	return powf((float)value, power);
}

// 整数を渡し、べき乗を返す
float Math::Pow(int value, float power)
{
	return powf((float)value, power);
}

// 実数を渡し、絶対値を返す
float Math::Abs(float value)
{
	return fabsf(value);
}

// 浮動小数点数を渡し、絶対値を返す
float Math::Abs(double value)
{
	return fabsf((float)value);
}

// 整数を渡し、絶対値を返す
float Math::Abs(int value)
{
	return fabsf((float)value);
}

// 実数を渡し、平方根を返す
float Math::Sqrt(float value)
{
	return sqrtf(value);
}

// 浮動小数点数を渡し、平方根を返す
float Math::Sqrt(double value)
{
	return sqrtf((float)value);
}

// 整数を渡し、平方根を返す
float Math::Sqrt(int value)
{
	return sqrtf((float)value);
}

// 値を指定された範囲内に制限します
float Math::Clamp(float value, float min, float max)
{
	assert(min < max && "Clampで最小値が最大値より大きい値が渡されました");
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

// 値を指定された範囲内に制限します
int Math::Clamp(int value, int min, int max)
{
	assert(min < max && "Clampで最小値が最大値より大きい値が渡されました");
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

//値を指定された範囲内で無限ループさせます
float Math::InfinityClamp(float value, float min, float max){
	if (value < min)
		return max;
	if (value > max)
		return min;
	return value;
}

//値を指定された範囲内で無限ループさせます
int Math::InfinityClamp(int value, int min, int max){
	if (value < min)
		return max;
	if (value > max)
		return min;
	return value;
}