#pragma once

#include "../math/Vector2.h"
#include "../math/Point.h"
#include <string>
#include <unordered_map>
#include <vector>

class Sprite
{
public:
	Sprite() = default;

	~Sprite();

	///<summary>
	/// ����������
	///</summary>
	void Initialize();

	///<summary>
	/// �ʏ�摜�̓ǂݍ���(�A�Z�b�g��)
	///</summary>
	void Load(const std::string& filename);
	///<summary>
	/// �����摜�̓ǂݍ���(�A�Z�b�g���A�������A���Əc�̕������A1�R�}�̑傫��)
	///</summary>
	void Load(const std::string& filename, int allnum, const Point& splitnum, const Point& size);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, float alpha);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]��)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l�A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, float alpha, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Point& size, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ�)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�A���t�@�l)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦�A��]��)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, float angle);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦�A��]��)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, float angle);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�A���t�@�l�A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦�A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Point& size, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);

	///<summary>
	/// �w��̌��Ԗڂ̕\���R�}�ԍ����擾����i�����A�~�������Ԗڂ̕\���R�}�ԍ��A�ő包���j
	///</summary>
	static int NumberFrame(int number, int digit, int maxdigit);

	bool IsASyncLoad(const std::string& name);

	int GetCount()
	{
		return static_cast<int>(m_sprites.size());
	}

	///<summary>
	/// �摜�̃T�C�Y���擾����
	///</summary>
	Point GetSize(const std::string& assetname) const
	{
		Point size;
		GetGraphSize(m_sprites.at(assetname), &size.x, &size.y);
		return size;
	}

private:
	///<summary>
	/// �t�@�C������'.'��������菜��
	///</summary>
	std::string Split(std::string filename);
	///<summary>
	/// �摜�ɃA���t�@�u�����h�������{��
	///</summary>
	void AlphaBlend(float alpha);
	///<summary>
	/// �摜�̃u�����h�������f�t�H���g�ɂ���
	///</summary>
	void DefaultBlend();

private:
	// �ʏ�摜
	std::unordered_map<std::string, int> m_sprites;
	// �����摜
	std::unordered_map<std::string, std::vector<int>> m_splitsprites;
	// �ǂݍ��񂾕����摜�̃R�}��
	std::unordered_map<std::string, Point> m_comma;
};