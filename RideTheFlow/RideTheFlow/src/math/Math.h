#pragma once

const static float PI = 3.14159265358979f;

class Math
{
public:
	Math() = default;
	~Math() = default;

	///<summary>
	/// 角度を渡し、正弦を返す
	///</summary>
	static float Sin(float angle);
	///<summary>
	/// 角度を渡し、正弦を返す
	///</summary>
	static float Sin(double angle);
	///<summary>
	/// 角度を渡し、正弦を返す
	///</summary>
	static float Sin(int angle);
	///<summary>
	/// 角度を渡し、余弦を返す
	///</summary>
	static float Cos(float angle);
	///<summary>
	/// 角度を渡し、余弦を返す
	///</summary>
	static float Cos(double angle);
	///<summary>
	/// 角度を渡し、余弦を返す
	///</summary>
	static float Cos(int angle);
	///<summary>
	/// 角度を渡し、正接を返す
	///</summary>
	static float Tan(float angle);
	///<summary>
	/// 角度を渡し、正接を返す
	///</summary>
	static float Tan(double angle);
	///<summary>
	/// 角度を渡し、正接を返す
	///</summary>
	static float Tan(int angle);
	///<summary>
	/// 角度を渡し、逆正弦をラジアンで返す
	///</summary>
	static float Asin(float angle);
	///<summary>
	/// 角度を渡し、逆正弦をラジアンで返す
	///</summary>
	static float Asin(double angle);
	///<summary>
	/// 角度を渡し、逆正弦をラジアンで返す
	///</summary>
	static float Asin(int angle);
	///<summary>
	/// 角度を渡し、逆余弦をラジアンで返す
	///</summary>
	static float Acos(float angle);
	///<summary>
	/// 角度を渡し、逆余弦をラジアンで返す
	///</summary>
	static float Acos(double angle);
	///<summary>
	/// 角度を渡し、逆余弦をラジアンで返す
	///</summary>
	static float Acos(int angle);
	///<summary>
	/// 角度を渡し、逆正接をラジアンで返す
	///</summary>
	static float Atan(float angle);
	///<summary>
	/// 角度を渡し、逆正接をラジアンで返す
	///</summary>
	static float Atan(double angle);
	///<summary>
	/// 角度を渡し、逆正接をラジアンで返す
	///</summary>
	static float Atan(int angle);
	static float Atan(float y, float x);
	///<summary>
	/// y / x の逆正接を返す
	///</summary>
	static float Atan2(float y, float x);
	///<summary>
	/// y / x の逆正接を返す
	///</summary>
	static float Atan2(double y, double x);
	///<summary>
	/// y / x の逆正接を返す
	///</summary>
	static float Atan2(int y, int x);
	///<summary>
	/// ラジアンを渡し、角度を返す
	///</summary>
	static float Degree(float radian);
	///<summary>
	/// 角度を渡し、ラジアンを返す
	///</summary>
	static float Radian(float degree);
	///<summary>
	/// 二つの実数を渡し、大きい方を返す
	///</summary>
	static float Max(float value1, float value2);
	///<summary>
	/// 二つの浮動小数点数を渡し、大きい方を返す
	///</summary>
	static float Max(double value1, double value2);
	///<summary>
	/// 二つの整数を渡し、大きい方を返す
	///</summary>
	static float Max(int value1, int value2);
	///<summary>
	/// 二つの実数を渡し、小さい方を返す
	///</summary>
	static float Min(float value1, float value2);
	///<summary>
	/// 二つの浮動小数点数を渡し、小さい方を返す
	///</summary>
	static float Min(double value1, double value2);
	///<summary>
	/// 二つの整数を渡し、小さい方を返す
	///</summary>
	static float Min(int value1, int value2);
	///<summary>
	/// 実数を渡し、べき乗を返す
	///</summary>
	static float Pow(float value, float power = 2.0f);
	///<summary>
	/// 浮動小数点数を渡し、べき乗を返す
	///</summary>
	static float Pow(double value, float power = 2.0f);
	///<summary>
	/// 整数を渡し、べき乗を返す
	///</summary>
	static float Pow(int value, float power = 2.0f);
	///<summary>
	/// 実数を渡し、絶対値を返す
	///</summary>
	static float Abs(float value);
	///<summary>
	/// 浮動小数点数を渡し、絶対値を返す
	///</summary>
	static float Abs(double value);
	///<summary>
	/// 整数を渡し、絶対値を返す
	///</summary>
	static float Abs(int value);

	template <class Type>
	static Type Abstemp(Type value)
	{
		return static_cast<Type>(0) > value ? -value : value;
	}

	///<summary>
	/// 線形補間
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
	* @brief ベジェ線形補間
	* @param[in] start : 開始値
	* @param[in] center : 中間値
	* @param[in] end : 終了値
	* @param[in] t : 時間比率
	* @note t = 0.0 ~ 1.0
	*
	* @return 3点間で補完された値を返す
	**********/
	template <typename T> inline
		static T Bezier(const T& start, const T& center, const T& end, float t)
	{
			return (((1.0f - t) * (1.0f - t) * start) + (2.0f * (1.0f - t) * (t * center)) + (t * t) * end);
		}

	///<summary>
	/// 実数を渡し、平方根を返す
	///</summary>
	static float Sqrt(float value);
	///<summary>
	/// 浮動小数点数を渡し、平方根を返す
	///</summary>
	static float Sqrt(double value);
	///<summary>
	/// 整数を渡し、平方根を返す
	///</summary>
	static float Sqrt(int value);
	///<summary>
	/// 値を指定された範囲内に制限します
	///</summary>
	static float Clamp(float value, float min, float max);
	///<summary>
	/// 値を指定された範囲内に制限します
	///</summary>
	static int Clamp(int value, int min, int max);

	//値を指定された範囲内で無限ループさせます
	static float InfinityClamp(float value, float min, float max);
	//値を指定された範囲内で無限ループさせます

	static int InfinityClamp(int value, int min, int max);
};