#pragma once

#include <Dxlib.h>
#include <string>

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3();
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(float s);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(float x, float y);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(float x, float y, float z);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(int s);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(int x, int y);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(int x, int y, int z);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(const Vector3& vector);
	///<summary>
	/// コンストラクタ
	///</summary>
	Vector3(const VECTOR& vector);

public:
	///<summary>
	/// (0,0,0)で初期化されたベクトル
	///</summary>
	static Vector3 Zero;
	///<summary>
	/// (1,1,1)で初期化されたベクトル
	///</summary>
	static Vector3 One;
	///<summary>
	/// (0,1,0)で初期化されたベクトル
	///</summary>
	static Vector3 Up;
	///<summary>
	/// (0,-1,0)で初期化されたベクトル
	///</summary>
	static Vector3 Down;
	///<summary>
	/// (-1,0,0)で初期化されたベクトル
	///</summary>
	static Vector3 Left;
	///<summary>
	/// (1,0,0)で初期化されたベクトル
	///</summary>
	static Vector3 Right;
	///<summary>
	/// (0,0,-1)で初期化されたベクトル
	///</summary>
	static Vector3 Forward;
	///<summary>
	/// (0,0,1)で初期化されたベクトル
	///</summary>
	static Vector3 Backward;

	//色
	static Vector3 White;
	static Vector3 Black;
	static Vector3 Blue;
	static Vector3 Red;
	static Vector3 Green;

public:
	///<summary>
	/// 自身のベクトルの大きさ（長さ）を返す
	///</summary>
	float Length() const;
	///<summary>
	/// 自身のベクトルを正規化する
	///</summary>
	void Normalize();
	///<summary>
	/// 自身の正規化されたベクトルを返す
	///</summary>
	Vector3 Normalized() const;

public:
	///<summary>
	/// ベクトルの大きさ（長さ）を返す
	///</summary>
	static float Length(const Vector3& v);
	///<summary>
	/// ２点間の距離を返す
	///</summary>
	static float Distance(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// ベクトルを正規化して返す
	///</summary>
	static Vector3 Normalize(const Vector3& v);
	///<summary>
	/// ２つのベクトルの内積を返す
	///</summary>
	static float Dot(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// ２つのベクトルの外積を返す
	///</summary>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// ２つのベクトルのなす角を返す
	///</summary>
	static float Inner(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// 前のベクトルを返す(座標、回転量)
	///</summary>
	static Vector3 FrontVec(Vector3& position, Vector3& rotation);
	///<summary>
	/// 二つのベクトル間の線形補間をする
	///</summary>
	static Vector3 Lerp(const Vector3& start, const Vector3& end, float amount);
	///<summary>
	/// バネの力を加える(現在の位置,バネの現在の移動速度,バネの静止位置,バネ定数,バネの強さ,摩擦力,質量)
	///</summary>
	static void Spring(Vector3& position, Vector3& velocity, const Vector3& restPosition, float stiffness, float friction, float mass);
	///<summary>
	/// ピッチを求め、ラジアンで返す
	///</summary>
	static float Pitch(const Vector3& front);
	///<summary>
	/// ヨーを求め、ラジアンで返す
	///</summary>
	static float Yaw(const Vector3& front);
	///<summary>
	/// 座標から座標へ向かう単位ベクトルを返す
	///</summary>
	static Vector3 Direction(const Vector3& start, const Vector3& end);

public:
	///<summary>
	/// Vector3型をVECTOR型に変換して返す
	///</summary>
	static VECTOR ToVECTOR(const Vector3& v);
	///<summary>
	/// 自身をVECTOR型に変換したものを返す
	///</summary>
	VECTOR ToVECTOR() const;
	///<summary>
	/// Vector3型をDWORD型に変換したものを返す
	///</summary>
	static DWORD ToColor(const Vector3& v);
	///<summary>
	/// 自身をDWORD型に変換したものを返す
	///</summary>
	DWORD ToColor() const;

public:
	Vector3& operator = (const Vector3& v);
	Vector3& operator = (const VECTOR& v);
	operator std::string() const;
	operator VECTOR() const;
};

Vector3 operator + (const Vector3& v1, const Vector3& v2);
Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3 operator - (const Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3 operator * (const Vector3& v, const float f);
Vector3 operator * (const float f, const Vector3& v);
Vector3 operator * (const Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v, const float f);
Vector3& operator *= (const float f, Vector3& v);
Vector3 operator / (const Vector3& v, const float f);
Vector3 operator / (const float f, const Vector3& v);
Vector3 operator / (const Vector3& v1, const Vector3& v2);
Vector3& operator /= (Vector3& v, const float f);
Vector3 operator - (const Vector3& v);
bool operator != (const Vector3& v1, const Vector3& v2);

VECTOR& operator += (const VECTOR& v1, const Vector3& v2);