#include "Matrix4.h"
#include "Math.h"
#include "Quaternion.h"
#include <sstream>

Matrix4 Matrix4::Zero = Matrix4(
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f);

Matrix4 Matrix4::Identity = Matrix4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 1.0f);

Matrix4::Matrix4()
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			m[i][j] = Identity.m[i][j];
		}
	}
}

Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Matrix4::Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3)
{
	m[0][0] = v0.x; m[0][1] = v0.y; m[0][2] = v0.z; m[0][3] = v0.w;
	m[1][0] = v1.x; m[1][1] = v1.y; m[1][2] = v1.z; m[1][3] = v1.w;
	m[2][0] = v2.x; m[2][1] = v2.y; m[2][2] = v2.z; m[2][3] = v2.w;
	m[3][0] = v3.x; m[3][1] = v3.y; m[3][2] = v3.z; m[3][3] = v3.w;
}

Matrix4::Matrix4(Vector3 scale, float rotateX, float rotateY, float rotateZ, Vector3 pos)
{

}

Vector3 Matrix4::GetPosition() const
{
	return GetPosition(*this);
}

Vector3 Matrix4::GetLeft() const
{
	return GetLeft(*this);
}

Vector3 Matrix4::GetUp() const
{
	return GetUp(*this);
}

Vector3 Matrix4::GetFront() const
{
	return GetFront(*this);
}

Vector3 Matrix4::GetScale() const
{
	return GetScale(*this);
}

Vector3 Matrix4::GetRotate() const
{
	return GetRotate(*this);
}

Vector3 Matrix4::GetRotateDegree() const
{
	return GetRotateDegree(*this);
}

void Matrix4::SetPosition(const Vector3& position)
{
	m[3][0] = position.x;
	m[3][1] = position.y;
	m[3][2] = position.z;
}

void Matrix4::SetLeft(const Vector3& left)
{
	m[0][0] = left.x;
	m[0][1] = left.y;
	m[0][2] = left.z;
}
void Matrix4::SetUp(const Vector3& up)
{
	m[1][0] = up.x;
	m[1][1] = up.y;
	m[1][2] = up.z;
}

void Matrix4::SetFront(const Vector3& front)
{
	m[2][0] = front.x;
	m[2][1] = front.y;
	m[2][2] = front.z;
}

Matrix4 Matrix4::Scale(const Vector3& s)
{
	Matrix4 result = {
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return result;
}

Matrix4 Matrix4::RotateX(float angle)
{
	float sin = Math::Sin(angle);
	float cos = Math::Cos(angle);
	Matrix4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos, sin, 0.0f,
		0.0f, -sin, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return result;
}

Matrix4 Matrix4::RotateY(float angle)
{
	float sin = Math::Sin(angle);
	float cos = Math::Cos(angle);
	Matrix4 result = {
		cos, 0.0f, -sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin, 0.0f, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return result;
}

Matrix4 Matrix4::RotateZ(float angle)
{
	float sin = Math::Sin(angle);
	float cos = Math::Cos(angle);
	Matrix4 result = {
		cos, sin, 0.0f, 0.0f,
		-sin, cos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return result;
}

Matrix4 Matrix4::Translate(const Vector3& t)
{
	Matrix4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		t.x, t.y, t.z, 1.0f
	};
	return result;
}

Matrix4 Matrix4::CreateMatrix(const Vector3& s, const float& rotateXangle, const float& rotateYangle, const float& rotateZangle, const Vector3& pos)
{
	Matrix4 result = Scale(s) * RotateZ(rotateZangle) * RotateX(rotateXangle) * RotateY(rotateYangle) * Translate(pos);
	return result;
}

Matrix4 Matrix4::CreateMatrix(const Matrix4& scale_, const Matrix4& rotateX_, const Matrix4& rotateY_, const Matrix4& rotateZ_, const Matrix4& translate_)
{
	Matrix4 result = scale_ * rotateZ_ * rotateX_ * rotateY_ * translate_;
	return result;
}

Vector3 Matrix4::Transform(const Vector3& v, const Matrix4& m)
{
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	Vector3 result = {
		(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
		(v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
		(v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w
	};
	return result;
}

Vector3 Matrix4::TransformRotateOnly(const Vector3& v, const Matrix4& m)
{
	Vector3 result = {
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
	return result;
}

Matrix4 Matrix4::Transpose(const Matrix4& m)
{
	Matrix4 result;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

Matrix4 Matrix4::TransposeRotateOnly(const Matrix4& m)
{
	Matrix4 result = m;
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

Matrix4 Matrix4::InverseFast(const Matrix4& m)
{
	// 回転行列の作成
	Matrix4 result = m;
	result.SetPosition(Vector3::Zero);
	// 回転行列の逆行列を作成
	result = Transpose(result);
	// 平行移動成分の逆変換
	Vector3 invPosition = -GetPosition(m) * result;
	// 逆行列を作成
	result.SetPosition(invPosition);
	return result;
}

Matrix4 Matrix4::Inverse(const Matrix4& m)
{
	float a0 = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
	float a1 = m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0];
	float a2 = m.m[0][0] * m.m[1][3] - m.m[0][3] * m.m[1][0];
	float a3 = m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1];
	float a4 = m.m[0][1] * m.m[1][3] - m.m[0][3] * m.m[1][1];
	float a5 = m.m[0][2] * m.m[1][3] - m.m[0][3] * m.m[1][2];
	float b0 = m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0];
	float b1 = m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0];
	float b2 = m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0];
	float b3 = m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1];
	float b4 = m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1];
	float b5 = m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2];
	float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	if (det == 0.0f) {
		return m; // 逆行列が存在しない！
	}
	float invDet = 1.0f / det;
	Matrix4 result = {
		(m.m[1][1] * b5 - m.m[1][2] * b4 + m.m[1][3] * b3) * invDet,
		(-m.m[0][1] * b5 + m.m[0][2] * b4 - m.m[0][3] * b3) * invDet,
		(m.m[3][1] * a5 - m.m[3][2] * a4 + m.m[3][3] * a3) * invDet,
		(-m.m[2][1] * a5 + m.m[2][2] * a4 - m.m[2][3] * a3) * invDet,
		(-m.m[1][0] * b5 + m.m[1][2] * b2 - m.m[1][3] * b1) * invDet,
		(m.m[0][0] * b5 - m.m[0][2] * b2 + m.m[0][3] * b1) * invDet,
		(-m.m[3][0] * a5 + m.m[3][2] * a2 - m.m[3][3] * a1) * invDet,
		(m.m[2][0] * a5 - m.m[2][2] * a2 + m.m[2][3] * a1) * invDet,
		(m.m[1][0] * b4 - m.m[1][1] * b2 + m.m[1][3] * b0) * invDet,
		(-m.m[0][0] * b4 + m.m[0][1] * b2 - m.m[0][3] * b0) * invDet,
		(m.m[3][0] * a4 - m.m[3][1] * a2 + m.m[3][3] * a0) * invDet,
		(-m.m[2][0] * a4 + m.m[2][1] * a2 - m.m[2][3] * a0) * invDet,
		(-m.m[1][0] * b3 + m.m[1][1] * b1 - m.m[1][2] * b0) * invDet,
		(m.m[0][0] * b3 - m.m[0][1] * b1 + m.m[0][2] * b0) * invDet,
		(-m.m[3][0] * a3 + m.m[3][1] * a1 - m.m[3][2] * a0) * invDet,
		(m.m[2][0] * a3 - m.m[2][1] * a1 + m.m[2][2] * a0) * invDet
	};
	return result;
}

Matrix4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 z = Vector3::Normalize(eye - at);
	Vector3 x = Vector3::Normalize(Vector3::Cross(up, z));
	Vector3 y = Vector3::Cross(z, x);
	Matrix4 result = {
		x.x, y.x, z.x, 0.0f,
		x.y, y.y, z.y, 0.0f,
		x.z, y.z, z.z, 0.0f,
		-Vector3::Dot(eye, x), -Vector3::Dot(eye, y), -Vector3::Dot(eye, z), 1.0f
	};
	return result;
}

Matrix4 Perspective(float fov, float aspect, float zn, float zf)
{
	float ys = 1.0f / Math::Tan(fov / 2.0f);
	float xs = ys / aspect;
	Matrix4 result = {
		xs, 0.0f, 0.0f, 0.0f,
		0.0f, ys, 0.0f, 0.0f,
		0.0f, 0.0f, (zf + zn) / (zn - zf), -1.0f,
		0.0f, 0.0f, (2.0f*zf*zn) / (zn - zf), 0.0f
	};
	return result;
}

Matrix4 Screen(float x, float y, float width, float height)
{
	float w = width / 2.0f;
	float h = height / 2.0f;
	Matrix4 result = {
		w, 0.0f, 0.0f, 0.0f,
		0.0f, -h, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		w + x, h + y, 0.0f, 1.0f
	};
	return result;
}

Vector3 Matrix4::GetPosition(const Matrix4& m)
{
	Vector3 result = { m.m[3][0], m.m[3][1], m.m[3][2] };
	return result;
}

Vector3 Matrix4::GetLeft(const Matrix4& m)
{
	Vector3 result = { m.m[0][0], m.m[0][1], m.m[0][2] };
	return result;
}

Vector3 Matrix4::GetUp(const Matrix4& m)
{
	Vector3 result = { m.m[1][0], m.m[1][1], m.m[1][2] };
	return result;
}

Vector3 Matrix4::GetFront(const Matrix4& m)
{
	Vector3 result = { m.m[2][0], m.m[2][1], m.m[2][2] };
	return result;
}

Vector3 Matrix4::GetScale(const Matrix4& m)
{
	Vector3 result = {
		GetLeft(m).Length(),
		GetUp(m).Length(),
		GetFront(m).Length()
	};
	return result;
}

Vector3 Matrix4::GetRotate(const Matrix4& m)
{
	Vector3 result = {
		Pitch(m),
		Yaw(m),
		Roll(m)
	};
	return result;
}

Vector3 Matrix4::GetRotateDegree(const Matrix4& m)
{
	Vector3 result = {
		Math::Degree(Pitch(m)),
		Math::Degree(Yaw(m)),
		Math::Degree(Roll(m))
	};
	return result;
}

Matrix4 Matrix4::SetPosition(Matrix4& m, const Vector3& position)
{
	Matrix4 result = m;
	result.m[3][0] = position.x;
	result.m[3][1] = position.y;
	result.m[3][2] = position.z;
	return result;
}

Matrix4 Matrix4::SetLeft(Matrix4& m, const Vector3& left)
{
	Matrix4 result = m;
	result.m[0][0] = left.x;
	result.m[0][1] = left.y;
	result.m[0][2] = left.z;
	return result;
}

Matrix4 Matrix4::SetUp(Matrix4& m, const Vector3& up)
{
	Matrix4 result = m;
	result.m[1][0] = up.x;
	result.m[1][1] = up.y;
	result.m[1][2] = up.z;
	return result;
}

Matrix4 Matrix4::SetFront(Matrix4& m, const Vector3& front)
{
	Matrix4 result = m;
	result.m[2][0] = front.x;
	result.m[2][1] = front.y;
	result.m[2][2] = front.z;
	return result;
}

Matrix4 Matrix4::Slerp(const Matrix4& start, const Matrix4& end, float t){
	//拡大縮小の補完
	Vector3 s = Vector3::Lerp(GetScale(start), GetScale(end), t);
	// 回転の補間
	Quaternion r = Quaternion::Slerp(Quaternion(NormalizeRotate(start)), Quaternion(NormalizeRotate(end)), t);
	// 位置の補間
	Vector3 p = Vector3::Lerp(GetPosition(start), GetPosition(end), t);
	// 補間行列を求める
	return Scale(s) * (Quaternion::Rotate(r)) * Translate(p);
}

Matrix4 Matrix4::Lerp(const Matrix4& start, const Matrix4& end, float t)
{
	Matrix4 m = {
		Math::Lerp(start.m[0][0], end.m[0][0], t), Math::Lerp(start.m[0][1], end.m[0][1], t), Math::Lerp(start.m[0][2], end.m[0][2], t), Math::Lerp(start.m[0][3], end.m[0][3], t),
		Math::Lerp(start.m[1][0], end.m[1][0], t), Math::Lerp(start.m[1][1], end.m[1][1], t), Math::Lerp(start.m[1][2], end.m[1][2], t), Math::Lerp(start.m[1][3], end.m[1][3], t),
		Math::Lerp(start.m[2][0], end.m[2][0], t), Math::Lerp(start.m[2][1], end.m[2][1], t), Math::Lerp(start.m[2][2], end.m[2][2], t), Math::Lerp(start.m[2][3], end.m[2][3], t),
		Math::Lerp(start.m[3][0], end.m[3][0], t), Math::Lerp(start.m[3][1], end.m[3][1], t), Math::Lerp(start.m[3][2], end.m[3][2], t), Math::Lerp(start.m[3][3], end.m[3][3], t)
	};
	return m;
}

float Matrix4::Pitch(const Matrix4& m)
{
	return Vector3::Pitch(GetFront(m));
}

float Matrix4::Yaw(const Matrix4& m)
{
	return Vector3::Yaw(GetFront(m));
}

float Matrix4::Roll(const Matrix4& m)
{
	return Math::Atan(m.m[0][1], m.m[1][1]);
}

Vector3 Matrix4::Project(
	const Vector3& position,
	const Matrix4& screen,
	const Matrix4& projection,
	const Matrix4& view,
	const Matrix4& world)
{
	return position * world * view * projection * screen;
}

Vector3 Matrix4::UnProject(
	const Vector3& position,
	const Matrix4& screen,
	const Matrix4& projection,
	const Matrix4& view,
	const Matrix4& world)
{
	return position * Inverse(world * view * projection * screen);
}

Matrix4 Matrix4::NormalizeRotate(const Matrix4& m)
{
	Matrix4 result = m;
	//前方向のベクトルを取得
	Vector3 front = GetFront(m);
	//上方向のベクトルを取得
	Vector3 up = GetUp(m);
	// 左方向のベクトルを求める
	Vector3 left = Vector3::Normalize(Vector3::Cross(up, front));
	// 上方向のベクトルを求める
	up = Vector3::Normalize(Vector3::Cross(front, left));
	// 前方向のベクトルを求める
	front = Vector3::Cross(left, up);
	result.SetLeft(left);
	result.SetUp(up);
	result.SetFront(front);
	return result;
}

MATRIX Matrix4::ToMATRIX(const Matrix4& m)
{
	MATRIX result;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			result.m[i][j] = m.m[i][j];
		}
	}
	return result;
}

MATRIX Matrix4::ToMATRIX() const
{
	return ToMATRIX(*this);
}

Matrix4& Matrix4::operator = (const Matrix4& m_)
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
 			m[i][j] = m_.m[i][j];
		}
	}
	return *this;
}

Matrix4::operator std::string() const
{
	std::stringstream ss;
	ss <<
		"( "
		<< m[0][0] << " , " << m[0][1] << " , " << m[0][2] << " , " << m[0][3] << " , "
		<< m[1][0] << " , " << m[1][1] << " , " << m[1][2] << " , " << m[1][3] << " , "
		<< m[2][0] << " , " << m[2][1] << " , " << m[2][2] << " , " << m[2][3] << " , "
		<< m[3][0] << " , " << m[3][1] << " , " << m[3][2] << " , " << m[3][3] << " )";
	return ss.str();
}

Matrix4& operator *= (Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result = Matrix4::Zero;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	m1 = result;
	return m1;
}

Matrix4 operator * (const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result = m1;
	return result *= m2;
}

Vector3 operator * (const Vector3& v, const Matrix4& m)
{
	return Matrix4::Transform(v, m);
}

Matrix4 Matrix4::ToMatrix4(const MATRIX& m){
	Matrix4 m1;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			m1.m[i][j] = m.m[i][j];
		}
	}

	return m1;
}