#pragma once

#include <Dxlib.h>
#include "Vector3.h"
#include "Vector4.h"
#include <string>

class Matrix4
{
public:
	float m[4][4];

public:
	/// <summary>
	/// ゼロ行列を返す
	/// </summary>
	static Matrix4 Zero;
	/// <summary>
	/// 単位行列を返す
	/// </summary>
	static Matrix4 Identity;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Matrix4();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Matrix4(
		float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13, 
		float m20, float m21, float m22, float m23, 
		float m30, float m31, float m32, float m33);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Matrix4(Vector3 scale, float rotateX, float rotateY, float rotateZ, Vector3 pos);

public:
	/// <summary>
	/// 自身の座標を返す
	/// </summary>
	Vector3 GetPosition() const;
	/// <summary>
	/// 自身の横を返す
	/// </summary>
	Vector3 GetLeft() const;
	/// <summary>
	/// 自身の上を返す
	/// </summary>
	Vector3 GetUp() const;
	/// <summary>
	/// 自身の前を返す
	/// </summary>
	Vector3 GetFront() const;
	/// <summary>
	/// 自身のスケールを返す
	/// </summary>
	Vector3 GetScale() const;
	/// <summary>
	/// 自身の各軸の回転量をラジアンで返す
	/// </summary>
	Vector3 GetRotate() const;
	/// <summary>
	/// 自身の各軸の回転量を角度で返す
	/// </summary>
	Vector3 GetRotateDegree() const;
	/// <summary>
	/// 座標をセットする
	/// </summary>
	void SetPosition(const Vector3& position);
	/// <summary>
	/// 左をセットする
	/// </summary>
	void SetLeft(const Vector3& left);
	/// <summary>
	/// 上をセットする
	/// </summary>
	void SetUp(const Vector3& up);
	/// <summary>
	/// 前をセットする
	/// </summary>
	void SetFront(const Vector3& front);

public:
	/// <summary>
	/// 拡大縮小行列
	/// </summary>
	static Matrix4 Scale(const Vector3& s);
	/// <summary>
	/// 回転行列X
	/// </summary>
	static Matrix4 RotateX(float angle);
	/// <summary>
	/// 回転行列Y
	/// </summary>
	static Matrix4 RotateY(float angle);
	/// <summary>
	/// 回転行列Z
	/// </summary>
	static Matrix4 RotateZ(float angle);
	/// <summary>
	/// 平行移動行列
	/// </summary>
	static Matrix4 Translate(const Vector3& pos);
	/// <summary>
	/// マトリックスを作成する スケール　X軸　Y軸　Z軸　移動量
	/// </summary>
	static Matrix4 CreateMatrix(const Vector3& s = Vector3::One, const float& rototeXangle = 0, const float& rotateYangle = 0, const float& rotateZangle = 0, const Vector3& pos = Vector3::Zero);
	/// <summary>
	/// マトリックスを作成する
	/// </summary>
	static Matrix4 CreateMatrix(const Matrix4& scale_ = Identity, const Matrix4& rotateX_ = Identity, const Matrix4& rotateY_ = Identity, const Matrix4& rotateZ_ = Identity, const Matrix4& translate_ = Identity);
	/// <summary>
	/// 座標変換(ベクトルと行列の積)
	/// </summary>
	static Vector3 Transform(const Vector3& v, const Matrix4& m);
	/// <summary>
	/// 座標変換(回転のみ)
	/// </summary>
	static Vector3 TransformRotateOnly(const Vector3& v, const Matrix4& m);
	/// <summary>
	/// 転置行列
	/// </summary>
	static Matrix4 Transpose(const Matrix4& m);
	static Matrix4 TransposeRotateOnly(const Matrix4& m);
	/// <summary>
	/// 逆行列(拡縮除く)
	/// </summary>
	static Matrix4 InverseFast(const Matrix4& m);
	/// <summary>
	/// 逆行列
	/// </summary>
	static Matrix4 Inverse(const Matrix4& m);

public:
	/// <summary>
	/// 視野変換行列
	/// </summary>
	static Matrix4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
	/// <summary>
	/// 透視変換行列を作成する
	/// </summary>
	static Matrix4 Perspective(float fov, float aspect, float zn, float zf);
	/// <summary>
	/// スクリーン座標変換行列を作成する
	/// </summary>
	static Matrix4 Screen(float x, float y, float width, float height);

public:
	/// <summary>
	/// 座標を返す
	/// </summary>
	static Vector3 GetPosition(const Matrix4& m);
	/// <summary>
	/// 横を返す
	/// </summary>
	static Vector3 GetLeft(const Matrix4& m);
	/// <summary>
	/// 上を返す
	/// </summary>
	static Vector3 GetUp(const Matrix4& m);
	/// <summary>
	/// 前を返す
	/// </summary>
	static Vector3 GetFront(const Matrix4& m);
	/// <summary>
	/// スケールを返す
	/// </summary>
	static Vector3 GetScale(const Matrix4& m);
	/// <summary>
	/// 各軸の回転量をラジアン返す
	/// </summary>
	static Vector3 GetRotate(const Matrix4& m);
	/// <summary>
	/// 各軸の回転量を角度で返す
	/// </summary>
	static Vector3 GetRotateDegree(const Matrix4& m);
	/// <summary>
	/// 座標をセットした行列を返す
	/// </summary>
	static Matrix4 SetPosition(Matrix4& m, const Vector3& position);
	/// <summary>
	/// 左をセットした行列を返す
	/// </summary>
	static Matrix4 SetLeft(Matrix4& m, const Vector3& left);
	/// <summary>
	/// 上をセットした行列を返す
	/// </summary>
	static Matrix4 SetUp(Matrix4& m, const Vector3& up);
	/// <summary>
	/// 前をセットした行列を返す
	/// </summary>
	static Matrix4 SetFront(Matrix4& m, const Vector3& front);
	/// <summary>
	/// 球面線形補間
	/// </summary>
	static Matrix4 Slerp(const Matrix4& start, const Matrix4& end, float t);
	/// <summary>
	/// 線形補間
	/// </summary>
	static Matrix4 Lerp(const Matrix4& start, const Matrix4& end, float t);
	/// <summary>
	/// ピッチ角(左右軸、上下方向回転量)を求める
	/// </summary>
	static float Pitch(const Matrix4& m);
	/// <summary>
	/// ヨー角(上下軸、前後方向回転量)を求める
	/// </summary>
	static float Yaw(const Matrix4& m);
	/// <summary>
	/// ロール角(前後軸、左右方向回転量)を求める
	/// </summary>
	static float Roll(const Matrix4& m);

	/// <summary>
	/// スクリーン変換
	/// </summary>
	static Vector3 Project(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);
	/// <summary>
	/// 画面の座標からローカル座標を求める
	/// </summary>
	static Vector3 UnProject(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);
	/// <summary>
	/// 回転行列の正規化
	/// </summary>
	static Matrix4 NormalizeRotate(const Matrix4& m);

public:
	///<summary>
	/// Matrix4型をMATRIX型に変換して返す
	///</summary>
	static MATRIX ToMATRIX(const Matrix4& m);
	///<summary>
	/// 自身をMATRIX型に変換したものを返す
	///</summary>
	MATRIX ToMATRIX() const;
	static Matrix4 ToMatrix4(const MATRIX& m);

public:
	Matrix4& operator = (const Matrix4& m_);
	operator std::string() const;
};

Matrix4& operator *= (Matrix4& m1, const Matrix4& m2);
Matrix4 operator * (const Matrix4& m1, const Matrix4& m2);
Vector3 operator * (const Vector3& v, const Matrix4& m);