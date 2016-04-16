#pragma once

#include <Dxlib.h>
#include <string>
class Point;

class Vector2
{
public:
	float x;
	float y;
public:
	/// <summary>
	/// (0, 0)で初期化されたベクトルを返す
	/// </summary>
	static Vector2 Zero;
	/// <summary>
	/// (1, 1)で初期化されたベクトルを返す
	/// </summary>
	static Vector2 One;
	/// <summary>
	/// (-1, 0)で初期化されたベクトルを返す
	/// </summary>
	static Vector2 Left;
	/// <summary>
	/// (1, 0)で初期化されたベクトルを返す
	/// </summary>
	static Vector2 Right;
	/// <summary>
	/// (0, -1)で初期化されたベクトルを返す
	/// </summary>
	static Vector2 Up;
	/// <summary>
	/// (0, 1)で初期化されたベクトルを返す
	/// </summary>
	static Vector2 Down;
	/// <summary>
	/// 画面中央の座標で初期化されたベクトルを返す
	/// </summary>
	static Vector2 Center();
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2(float x, float y);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2(int x, int y);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2(const Vector2& vec);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2(const VECTOR& vec);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2(float s);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2(int s);
public:
	/// <summary>
	/// 自身のベクトルの大きさ（長さ）を返す
	/// </summary>
	float Length() const;
	/// <summary>
	/// 自身のベクトルの大きさ（長さ）の二乗を返す
	/// </summary>
	float LengthPow2() const;
	/// <summary>
	/// ２点間の距離を返す
	/// </summary>
	float Distance(const Vector2& other) const;
	/// <summary>
	/// ２点間の距離の二乗を返す
	/// </summary>
	float DistancePow2(const Vector2& other) const;
	/// <summary>
	/// 自身のベクトルを正規化する
	/// </summary>
	void Normalize();
	/// <summary>
	/// 自身の正規化されたベクトルを返す
	/// </summary>
	Vector2 Normalized() const;
	/// <summary>
	/// 自身と相手のベクトルの内積を返す
	/// </summary>
	float Dot(const Vector2& v) const;
	/// <summary>
	/// 自身と相手のベクトルのなす角を返す
	/// </summary>
	float Inner(const Vector2& v) const;
public:
	/// <summary>
	/// ベクトルを正規化する
	/// </summary>
	static Vector2 Normalize(const Vector2& v);
	/// <summary>
	/// ２点間の距離を返す
	/// </summary>
	static float Distance(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// ２点間の距離の二乗を返す
	/// </summary>
	static float DistancePow2(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// ２つのベクトルの内積を返す
	/// </summary>
	static float Dot(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// ２つのベクトルのなす角を返す
	/// </summary>
	static float Inner(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// 二つのベクトルの外積を返す
	/// </summary>
	static float Cross(const Vector2& v1, const Vector2& v2);
	///<summary>
	/// 二つのベクトル間の線形補間する
	///</summary>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float amount);
	
public:
	///<summary>
	/// Vector2型をPoint型に変換して返す
	///</summary>
	static Point ToPoint(const Vector2& v);
	///<summary>
	/// 自身をVECTOR型に変換したものを返す
	///</summary>
	Point ToPoint() const;

public:
	Vector2& operator = (const Vector2& v);
	operator std::string() const;
};

Vector2 operator + (const Vector2& v1, const Vector2& v2);
Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2 operator - (const Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2 operator * (const Vector2& v, const float f);
Vector2 operator * (const float f, const Vector2& v);
Vector2& operator *= (Vector2& v, const float f);
Vector2& operator *= (const float f, Vector2& v);
Vector2 operator / (const Vector2& v, const float f);
Vector2 operator / (const float f, const Vector2& v);
Vector2& operator /= (Vector2& v, const float f);
Vector2 operator - (const Vector2& v);