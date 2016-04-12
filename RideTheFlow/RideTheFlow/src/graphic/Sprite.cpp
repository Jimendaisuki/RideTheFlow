#include "Sprite.h"
#include "../game/WorkFolder.h"
#include <Dxlib.h>
#include <sstream>
#include <string>
#include <iomanip>

#define PI 3.14159265358979

Sprite::~Sprite()
{
	InitGraph();
}

// ����������
void Sprite::Initialize()
{
	InitGraph();
	m_sprites.clear();
	m_splitsprites.clear();
}

// �ʏ�摜�̓ǂݍ���
void Sprite::Load(const std::string& filename)
{
	m_sprites[Split(filename)] = LoadGraph((WorkFolder::Name + filename).c_str());
}

// �����摜�̓ǂݍ���
void Sprite::Load(const std::string& filename, int allnum, const Point& splitnum, const Point& size)
{
	int* handle = new int[allnum];
	LoadDivGraph((WorkFolder::Name + filename).c_str(), allnum, splitnum.x, splitnum.y, size.x, size.y, handle);
	for (int i = 0; i < allnum; ++i)
	{
		m_splitsprites[Split(filename)].emplace_back(handle[i]);
	}
	m_comma[Split(filename)] = splitnum;
	delete[] handle;
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W)
void Sprite::Draw(const std::string& assetname, const Vector2& position)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0f, 1.0f, 0.0, m_sprites[assetname], true, false);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l)
void Sprite::Draw(const std::string& assetname, const Vector2& position, float alpha = 1.0f)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0f, 1.0f, 0.0, m_sprites[assetname], true, false);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], true, false);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], true, false);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_sprites[assetname], true, false);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_sprites[assetname], true, false);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���߁A���]) 
void Sprite::Draw(const std::string& assetname, const Vector2& position, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_sprites[assetname], trans, turn);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l�A���߁A���])
void Sprite::Draw(const std::string& assetname, const Vector2& position, float alpha = 1.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_sprites[assetname], trans, turn);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A���߁A���])
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], trans, turn);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], trans, turn);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[assetname], trans, turn);
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[assetname], trans, turn);
	DefaultBlend();
}

// �ʏ�摜�̕`��(�A�Z�b�g���A���W�A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Point& size, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	int handle = DerivationGraph(0, 0, size.x, size.y, m_sprites[assetname]);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, handle, trans, turn);
	DeleteGraph(handle);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], true, false);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha = 1.0f)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], true, false);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], true, false);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], true, false);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_splitsprites[assetname][frame], true, false);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]��)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_splitsprites[assetname][frame], true, false);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���߁A���]) 
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], trans, turn);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A�A���t�@�l�A���߁A���])
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha = 1.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], trans, turn);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A���߁A���])
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], trans, turn);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A���߁A���])
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], trans, turn);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�g�嗦�A��]���A���߁A���])
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_splitsprites[assetname][frame], trans, turn);
}

// �����摜�̕`��(�A�Z�b�g���A���W�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_splitsprites[assetname][frame], trans, turn);
	DefaultBlend();
}

// �����摜�̕`��(�A�Z�b�g���A���W�A�\���R�}�ԍ��A�\����`�T�C�Y�A���_�A�A���t�@�l�A�g�嗦�A��]���A���߁A���])
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Point& size, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	/*Point graphsize;
	GetGraphSize(m_splitsprites[assetname][frame], &graphsize.x, &graphsize.y);*/
	int handle = DerivationGraph(0, 0, size.x, size.y, m_splitsprites[assetname][frame]);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, handle, trans, turn);
	DeleteGraph(handle);
	DefaultBlend();
}

// �w��̌��Ԗڂ̕\���R�}�ԍ����擾����i�����A�~�������Ԗڂ̕\���R�}�ԍ��A�ő包���j
int Sprite::NumberFrame(int number, int digit, int maxdigit)
{
	// �T���ɑ�����string�^�ɕϊ�
	std::ostringstream ost;
	ost << std::setfill('0') << std::setw(maxdigit) << number;
	const std::string& str = ost.str();

	std::vector<char> score;
	score.clear();

	// �P��������vector�Ɋi�[
	for (auto& s : str)
	{
		score.push_back(s);
	}

	// �ݒ肳�ꂽ���Ԗڂɂ���X�R�A���Z�b�g����
	return score[maxdigit - digit] - '0';
}

// �t�@�C������'.'��������菜��
std::string Sprite::Split(std::string filename)
{
	std::string assetname;
	std::getline(
		std::stringstream(filename),
		assetname,
		'.'
	);
	return assetname;
}

// �摜�ɃA���t�@�u�����h�������{��
void Sprite::AlphaBlend(float alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f * alpha));
}

// �摜�̃u�����h�������f�t�H���g�ɂ���
void Sprite::DefaultBlend()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool Sprite::IsASyncLoad(const std::string& name)
{
	return CheckHandleASyncLoad(m_sprites[name]) == FALSE;
}