#pragma once

#include "Vector3.h"
#include "Matrix4.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	///<summary>
	/// コンストラクタ
	///</summary>
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	///<summary>
	/// コンストラクタ
	///</summary>
	Quaternion(const Vector3& v, float angle);
	///<summary>
	/// コンストラクタ(回転行列からクウォータニオンを作成)
	///</summary>
	Quaternion(const Matrix4& m);

public:
	///<summary>
	/// 内積を返す
	///</summary>
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	///<summary>
	/// 大きさ（長さ）を返す
	///</summary>
	static float Length(const Quaternion& q);
	///<summary>
	/// 正規化をする
	///</summary>
	static Quaternion Normalize(const Quaternion& q);
	///<summary>
	/// 球面線形補間
	///</summary>
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
	///<summary>
	/// クォータニオンを回転行列にして返す
	///</summary>
	static Matrix4 Rotate(const Quaternion& q);
	///<summary>
	/// 任意軸周りの回転行列を返す
	///</summary>
	static Matrix4 RotateAxis(const Vector3& v, float angle);
};

// 単項演算子オーバーロード
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);
// 代入演算子オーバーロード
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);
// ２項演算子オーバーロード
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);