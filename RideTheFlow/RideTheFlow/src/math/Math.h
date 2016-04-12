#pragma once

const static float PI = 3.14159265358979f;

class Math
{
public:
	Math() = default;
	~Math() = default;

	///<summary>
	/// Šp“x‚ğ“n‚µA³Œ·‚ğ•Ô‚·
	///</summary>
	static float Sin(float angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA³Œ·‚ğ•Ô‚·
	///</summary>
	static float Sin(double angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA³Œ·‚ğ•Ô‚·
	///</summary>
	static float Sin(int angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA—]Œ·‚ğ•Ô‚·
	///</summary>
	static float Cos(float angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA—]Œ·‚ğ•Ô‚·
	///</summary>
	static float Cos(double angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA—]Œ·‚ğ•Ô‚·
	///</summary>
	static float Cos(int angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA³Ú‚ğ•Ô‚·
	///</summary>
	static float Tan(float angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA³Ú‚ğ•Ô‚·
	///</summary>
	static float Tan(double angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA³Ú‚ğ•Ô‚·
	///</summary>
	static float Tan(int angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t³Œ·‚ğ•Ô‚·
	///</summary>
	static float Asin(float angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t³Œ·‚ğ•Ô‚·
	///</summary>
	static float Asin(double angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t³Œ·‚ğ•Ô‚·
	///</summary>
	static float Asin(int angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t—]Œ·‚ğ•Ô‚·
	///</summary>
	static float Acos(float angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t—]Œ·‚ğ•Ô‚·
	///</summary>
	static float Acos(double angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t—]Œ·‚ğ•Ô‚·
	///</summary>
	static float Acos(int angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t³Ú‚ğ•Ô‚·
	///</summary>
	static float Atan(float angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t³Ú‚ğ•Ô‚·
	///</summary>
	static float Atan(double angle);
	///<summary>
	/// Šp“x‚ğ“n‚µA‹t³Ú‚ğ•Ô‚·
	///</summary>
	static float Atan(int angle);
	static float Atan(float y, float x);
	///<summary>
	/// y / x ‚Ì‹t³Ú‚ğ•Ô‚·
	///</summary>
	static float Atan2(float y, float x);
	///<summary>
	/// y / x ‚Ì‹t³Ú‚ğ•Ô‚·
	///</summary>
	static float Atan2(double y, double x);
	///<summary>
	/// y / x ‚Ì‹t³Ú‚ğ•Ô‚·
	///</summary>
	static float Atan2(int y, int x);
	///<summary>
	/// ƒ‰ƒWƒAƒ“‚ğ“n‚µAŠp“x‚ğ•Ô‚·
	///</summary>
	static float Degree(float radian);
	///<summary>
	/// Šp“x‚ğ“n‚µAƒ‰ƒWƒAƒ“‚ğ•Ô‚·
	///</summary>
	static float Radian(float degree);
	///<summary>
	/// “ñ‚Â‚ÌÀ”‚ğ“n‚µA‘å‚«‚¢•û‚ğ•Ô‚·
	///</summary>
	static float Max(float value1, float value2);
	///<summary>
	/// “ñ‚Â‚Ì•‚“®¬”“_”‚ğ“n‚µA‘å‚«‚¢•û‚ğ•Ô‚·
	///</summary>
	static float Max(double value1, double value2);
	///<summary>
	/// “ñ‚Â‚Ì®”‚ğ“n‚µA‘å‚«‚¢•û‚ğ•Ô‚·
	///</summary>
	static float Max(int value1, int value2);
	///<summary>
	/// “ñ‚Â‚ÌÀ”‚ğ“n‚µA¬‚³‚¢•û‚ğ•Ô‚·
	///</summary>
	static float Min(float value1, float value2);
	///<summary>
	/// “ñ‚Â‚Ì•‚“®¬”“_”‚ğ“n‚µA¬‚³‚¢•û‚ğ•Ô‚·
	///</summary>
	static float Min(double value1, double value2);
	///<summary>
	/// “ñ‚Â‚Ì®”‚ğ“n‚µA¬‚³‚¢•û‚ğ•Ô‚·
	///</summary>
	static float Min(int value1, int value2);
	///<summary>
	/// À”‚ğ“n‚µA‚×‚«æ‚ğ•Ô‚·
	///</summary>
	static float Pow(float value, float power = 2.0f);
	///<summary>
	/// •‚“®¬”“_”‚ğ“n‚µA‚×‚«æ‚ğ•Ô‚·
	///</summary>
	static float Pow(double value, float power = 2.0f);
	///<summary>
	/// ®”‚ğ“n‚µA‚×‚«æ‚ğ•Ô‚·
	///</summary>
	static float Pow(int value, float power = 2.0f);
	///<summary>
	/// À”‚ğ“n‚µAâ‘Î’l‚ğ•Ô‚·
	///</summary>
	static float Abs(float value);
	///<summary>
	/// •‚“®¬”“_”‚ğ“n‚µAâ‘Î’l‚ğ•Ô‚·
	///</summary>
	static float Abs(double value);
	///<summary>
	/// ®”‚ğ“n‚µAâ‘Î’l‚ğ•Ô‚·
	///</summary>
	static float Abs(int value);

	template <class Type>
	static Type Abstemp(Type value)
	{
		return static_cast<Type>(0) > value ? -value : value;
	}

	///<summary>
	/// üŒ`•âŠÔ
	///</summary>
	template <typename T> static T Lerp(const T& start, const T& end, float amount)
	{
		if (amount < 0.0f) {
			amount = 0.0f;
		}
		else if (amount > 1.0f) {
			amount = 1.0f;
		}
		return start * (1.0f - amount) + end * amount;
	}

	/**********
	* @brief ƒxƒWƒFüŒ`•âŠÔ
	* @param[in] start : ŠJn’l
	* @param[in] center : ’†ŠÔ’l
	* @param[in] end : I—¹’l
	* @param[in] t : ŠÔ”ä—¦
	* @note t = 0.0 ~ 1.0
	*
	* @return 3“_ŠÔ‚Å•âŠ®‚³‚ê‚½’l‚ğ•Ô‚·
	**********/
	template <typename T> inline
		static T Bezier(const T& start, const T& center, const T& end, float t)
	{
			return (((1.0f - t) * (1.0f - t) * start) + (2.0f * (1.0f - t) * (t * center)) + (t * t) * end);
		}

	///<summary>
	/// À”‚ğ“n‚µA•½•ûª‚ğ•Ô‚·
	///</summary>
	static float Sqrt(float value);
	///<summary>
	/// •‚“®¬”“_”‚ğ“n‚µA•½•ûª‚ğ•Ô‚·
	///</summary>
	static float Sqrt(double value);
	///<summary>
	/// ®”‚ğ“n‚µA•½•ûª‚ğ•Ô‚·
	///</summary>
	static float Sqrt(int value);
	///<summary>
	/// ’l‚ğw’è‚³‚ê‚½”ÍˆÍ“à‚É§ŒÀ‚µ‚Ü‚·
	///</summary>
	static float Clamp(float value, float min, float max);
	///<summary>
	/// ’l‚ğw’è‚³‚ê‚½”ÍˆÍ“à‚É§ŒÀ‚µ‚Ü‚·
	///</summary>
	static int Clamp(int value, int min, int max);
};