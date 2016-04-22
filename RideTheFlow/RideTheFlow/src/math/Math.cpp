#include "Math.h"
#include <math.h>
#include <cassert>

// Šp“x‚ğ“n‚µASin‚ğ•Ô‚·
float Math::Sin(float angle)
{
	return sinf(Radian(angle));
}

// Šp“x‚ğ“n‚µASin‚ğ•Ô‚·
float Math::Sin(double angle)
{
	return sinf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µASin‚ğ•Ô‚·
float Math::Sin(int angle)
{
	return sinf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µACos‚ğ•Ô‚·
float Math::Cos(float angle)
{
	return cosf(Radian(angle));
}

// Šp“x‚ğ“n‚µACos‚ğ•Ô‚·
float Math::Cos(double angle)
{
	return cosf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µACos‚ğ•Ô‚·
float Math::Cos(int angle)
{
	return cosf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µATan‚ğ•Ô‚·
float Math::Tan(float angle)
{
	return tanf(Radian(angle));
}

// Šp“x‚ğ“n‚µATan‚ğ•Ô‚·
float Math::Tan(double angle)
{
	return tanf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µATan‚ğ•Ô‚·
float Math::Tan(int angle)
{
	return tanf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µA‹t³Œ·‚ğ•Ô‚·
float Math::Asin(float angle)
{
	return asinf(Radian(angle));
}

// Šp“x‚ğ“n‚µA‹t³Œ·‚ğ•Ô‚·
float Math::Asin(double angle)
{
	return asinf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µA‹t³Œ·‚ğ•Ô‚·
float Math::Asin(int angle)
{
	return asinf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µA‹t—]Œ·‚ğ•Ô‚·
float Math::Acos(float angle)
{
	return acosf(Radian(angle));
}

// Šp“x‚ğ“n‚µA‹t—]Œ·‚ğ•Ô‚·
float Math::Acos(double angle)
{
	return acosf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µA‹t—]Œ·‚ğ•Ô‚·
float Math::Acos(int angle)
{
	return acosf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µA‹t³Ú‚ğ•Ô‚·
float Math::Atan(float angle)
{
	return atanf(Radian(angle));
}

// Šp“x‚ğ“n‚µA‹t³Ú‚ğ•Ô‚·
float Math::Atan(double angle)
{
	return atanf(Radian((float)angle));
}

// Šp“x‚ğ“n‚µA‹t³Ú‚ğ•Ô‚·
float Math::Atan(int angle)
{
	return atanf(Radian((float)angle));
}

float Math::Atan(float y, float x)
{
	return atan2(y, x);
}

// y / x ‚Ì‹t³Ú‚ğ•Ô‚·
float Math::Atan2(float y, float x)
{
	return atan2f(Radian(y), Radian(x));
}

// y / x ‚Ì‹t³Ú‚ğ•Ô‚·
float Math::Atan2(double y, double x)
{
	return atan2f(Radian((float)y), Radian((float)x));
}

// y / x ‚Ì‹t³Ú‚ğ•Ô‚·
float Math::Atan2(int y, int x)
{
	return atan2f(Radian((float)y), Radian((float)x));
}

// ƒ‰ƒWƒAƒ“‚ğ“n‚µAŠp“x‚ğ•Ô‚·
float Math::Degree(float radian)
{
	return radian / PI * 180.0f;
}

// Šp“x‚ğ“n‚µAƒ‰ƒWƒAƒ“‚ğ•Ô‚·
float Math::Radian(float degree)
{
	return degree * PI / 180.0f;
}

// “ñ‚Â‚ÌÀ”‚ğ“n‚µA‘å‚«‚¢•û‚ğ•Ô‚·
float Math::Max(float value1, float value2)
{
	return fmaxf(value1, value2);
}

// “ñ‚Â‚Ì•‚“®¬”“_”‚ğ“n‚µA‘å‚«‚¢•û‚ğ•Ô‚·
float Math::Max(double value1, double value2)
{
	return fmaxf((float)value1, (float)value2);
}

// “ñ‚Â‚Ì®”‚ğ“n‚µA‘å‚«‚¢•û‚ğ•Ô‚·
float Math::Max(int value1, int value2)
{
	return fmaxf((float)value1, (float)value2);
}

// “ñ‚Â‚ÌÀ”‚ğ“n‚µA¬‚³‚¢•û‚ğ•Ô‚·
float Math::Min(float value1, float value2)
{
	return fminf(value1, value2);
}

// “ñ‚Â‚Ì•‚“®¬”“_”‚ğ“n‚µA¬‚³‚¢•û‚ğ•Ô‚·
float Math::Min(double value1, double value2)
{
	return fminf((float)value1, (float)value2);
}

// “ñ‚Â‚Ì®”‚ğ“n‚µA¬‚³‚¢•û‚ğ•Ô‚·
float Math::Min(int value1, int value2)
{
	return fminf((float)value1, (float)value2);
}

// À”‚ğ“n‚µA‚×‚«æ‚ğ•Ô‚·
float Math::Pow(float value, float power)
{
	return powf(value, power);
}

// •‚“®¬”“_”‚ğ“n‚µA‚×‚«æ‚ğ•Ô‚·
float Math::Pow(double value, float power)
{
	return powf((float)value, power);
}

// ®”‚ğ“n‚µA‚×‚«æ‚ğ•Ô‚·
float Math::Pow(int value, float power)
{
	return powf((float)value, power);
}

// À”‚ğ“n‚µAâ‘Î’l‚ğ•Ô‚·
float Math::Abs(float value)
{
	return fabsf(value);
}

// •‚“®¬”“_”‚ğ“n‚µAâ‘Î’l‚ğ•Ô‚·
float Math::Abs(double value)
{
	return fabsf((float)value);
}

// ®”‚ğ“n‚µAâ‘Î’l‚ğ•Ô‚·
float Math::Abs(int value)
{
	return fabsf((float)value);
}

// À”‚ğ“n‚µA•½•ûª‚ğ•Ô‚·
float Math::Sqrt(float value)
{
	return sqrtf(value);
}

// •‚“®¬”“_”‚ğ“n‚µA•½•ûª‚ğ•Ô‚·
float Math::Sqrt(double value)
{
	return sqrtf((float)value);
}

// ®”‚ğ“n‚µA•½•ûª‚ğ•Ô‚·
float Math::Sqrt(int value)
{
	return sqrtf((float)value);
}

// ’l‚ğw’è‚³‚ê‚½”ÍˆÍ“à‚É§ŒÀ‚µ‚Ü‚·
float Math::Clamp(float value, float min, float max)
{
	assert(min < max && "Clamp‚ÅÅ¬’l‚ªÅ‘å’l‚æ‚è‘å‚«‚¢’l‚ª“n‚³‚ê‚Ü‚µ‚½");
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

// ’l‚ğw’è‚³‚ê‚½”ÍˆÍ“à‚É§ŒÀ‚µ‚Ü‚·
int Math::Clamp(int value, int min, int max)
{
	assert(min < max && "Clamp‚ÅÅ¬’l‚ªÅ‘å’l‚æ‚è‘å‚«‚¢’l‚ª“n‚³‚ê‚Ü‚µ‚½");
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

//’l‚ğw’è‚³‚ê‚½”ÍˆÍ“à‚Å–³ŒÀƒ‹[ƒv‚³‚¹‚Ü‚·
float Math::InfinityClamp(float value, float min, float max){
	if (value < min)
		return max;
	if (value > max)
		return min;
	return value;
}

//’l‚ğw’è‚³‚ê‚½”ÍˆÍ“à‚Å–³ŒÀƒ‹[ƒv‚³‚¹‚Ü‚·
int Math::InfinityClamp(int value, int min, int max){
	if (value < min)
		return max;
	if (value > max)
		return min;
	return value;
}