#pragma once

#include <Dxlib.h>
#include <string>
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"

class TextDraw
{
private:
	TextDraw() = default;
	~TextDraw() = default;

public:
	static TextDraw &GetInstance(){
		static TextDraw t;
		return t;
	}

	/// <summary>
	/// ���������ʏ�̍��W(0,0)�ɔ������ŕ`�悷��
	/// </summary>
	void Draw(const std::string& s);



	/// <summary>
	/// ������𔒕����ŕ`�悷�� ( ���W , ������ )
	/// </summary>
	void Draw(const Vector2& pos, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , ������ )
	/// </summary>
	void Draw(const Vector2& pos, const Vector3& color, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�Y , ������ )
	/// </summary>
	void Draw(const Vector2& pos, const Vector3& color, const float& size, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�Y , ������ )
	/// </summary>
	void Draw(const Vector2& pos, const Vector3& color, const double& size, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�YX , �����T�C�YY , ������ )
	/// </summary>
	void Draw(const Vector2& pos, const Vector3& color, const float& sizeX, const float& sizeY, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�YX , �����T�C�YY , ������ )
	/// </summary>
	void Draw(const Vector2& pos, const Vector3& color, const double& sizeX, const double& sizeY, const std::string& s);


	/// <summary>
	/// ������𔒕����ŕ`�悷�� ( ���W , ������ )
	/// </summary>
	void Draw(const Point& pos, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , ������ )
	/// </summary>
	void Draw(const Point& pos, const Vector3& color, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�Y , ������ )
	/// </summary>
	void Draw(const Point& pos, const Vector3& color, const float& size, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�Y , ������ )
	/// </summary>
	void Draw(const Point& pos, const Vector3& color, const double& size, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�YX , �����T�C�YY , ������ )
	/// </summary>
	void Draw(const Point& pos, const Vector3& color, const float& sizeX, const float& sizeY, const std::string& s);
	/// <summary>
	/// �������`�悷�� ( ���W , �F(0,0,0)�`(255,255,255) , �����T�C�YX , �����T�C�YY , ������ )
	/// </summary>
	void Draw(const Point& pos, const Vector3& color, const double& sizeX, const double& sizeY, const std::string& s);
};