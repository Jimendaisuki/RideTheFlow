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

// 初期化処理
void Sprite::Initialize()
{
	InitGraph();
	m_sprites.clear();
	m_splitsprites.clear();
}

// 通常画像の読み込み
void Sprite::Load(const std::string& filename)
{
	m_sprites[Split(filename)] = LoadGraph((WorkFolder::Name + filename).c_str());
}

// 分割画像の読み込み
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

// 通常画像の描画(アセット名、座標)
void Sprite::Draw(const std::string& assetname, const Vector2& position)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0f, 1.0f, 0.0, m_sprites[assetname], true, false);
}

// 通常画像の描画(アセット名、座標、アルファ値)
void Sprite::Draw(const std::string& assetname, const Vector2& position, float alpha = 1.0f)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0f, 1.0f, 0.0, m_sprites[assetname], true, false);
	DefaultBlend();
}

// 通常画像の描画(アセット名、座標、原点、拡大率)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], true, false);
}

// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], true, false);
	DefaultBlend();
}

// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_sprites[assetname], true, false);
}

// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_sprites[assetname], true, false);
	DefaultBlend();
}

// 通常画像の描画(アセット名、座標、透過、反転) 
void Sprite::Draw(const std::string& assetname, const Vector2& position, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_sprites[assetname], trans, turn);
}

// 通常画像の描画(アセット名、座標、アルファ値、透過、反転)
void Sprite::Draw(const std::string& assetname, const Vector2& position, float alpha = 1.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_sprites[assetname], trans, turn);
	DefaultBlend();
}

// 通常画像の描画(アセット名、座標、原点、拡大率、透過、反転)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], trans, turn);
}

// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、透過、反転)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_sprites[assetname], trans, turn);
	DefaultBlend();
}

// 通常画像の描画(アセット名、座標、原点、拡大率、回転率、透過、反転)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[assetname], trans, turn);
}

// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率、透過、反転)
void Sprite::Draw(const std::string& assetname, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_sprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_sprites[assetname], trans, turn);
	DefaultBlend();
}

// 通常画像の描画(アセット名、座標、表示矩形サイズ、原点、アルファ値、拡大率、回転率、透過、反転)
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

// 分割画像の描画(アセット名、座標)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], true, false);
}

// 分割画像の描画(アセット名、座標、アルファ値)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha = 1.0f)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], true, false);
	DefaultBlend();
}

// 分割画像の描画(アセット名、座標、原点、拡大率)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], true, false);
}

// 分割画像の描画(アセット名、座標、原点、アルファ値、拡大率)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], true, false);
	DefaultBlend();
}

// 分割画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_splitsprites[assetname][frame], true, false);
}

// 分割画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle * PI / 180.0, m_splitsprites[assetname][frame], true, false);
	DefaultBlend();
}

// 分割画像の描画(アセット名、座標、透過、反転) 
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], trans, turn);
}

// 分割画像の描画(アセット名、座標、アルファ値、透過、反転)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha = 1.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, 0, 0,
		1.0, 1.0, 0.0, m_splitsprites[assetname][frame], trans, turn);
	DefaultBlend();
}

// 分割画像の描画(アセット名、座標、原点、拡大率、透過、反転)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], trans, turn);
}

// 分割画像の描画(アセット名、座標、原点、アルファ値、拡大率、透過、反転)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, 0.0, m_splitsprites[assetname][frame], trans, turn);
	DefaultBlend();
}

// 分割画像の描画(アセット名、座標、原点、拡大率、回転率、透過、反転)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_splitsprites[assetname][frame], trans, turn);
}

// 分割画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率、透過、反転)
void Sprite::SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)
{
	WorkFolder::CheckName(assetname, m_splitsprites);
	AlphaBlend(alpha);
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, (double)angle * PI / 180.0, m_splitsprites[assetname][frame], trans, turn);
	DefaultBlend();
}

// 分割画像の描画(アセット名、座標、表示コマ番号、表示矩形サイズ、原点、アルファ値、拡大率、回転率、透過、反転)
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

// 指定の桁番目の表示コマ番号を取得する（数字、欲しい桁番目の表示コマ番号、最大桁数）
int Sprite::NumberFrame(int number, int digit, int maxdigit)
{
	// ５桁に揃えたstring型に変換
	std::ostringstream ost;
	ost << std::setfill('0') << std::setw(maxdigit) << number;
	const std::string& str = ost.str();

	std::vector<char> score;
	score.clear();

	// １文字ずつvectorに格納
	for (auto& s : str)
	{
		score.push_back(s);
	}

	// 設定された桁番目にあるスコアをセットする
	return score[maxdigit - digit] - '0';
}

// ファイル名の'.'から後を取り除く
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

// 画像にアルファブレンド処理を施す
void Sprite::AlphaBlend(float alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f * alpha));
}

// 画像のブレンド処理をデフォルトにする
void Sprite::DefaultBlend()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool Sprite::IsASyncLoad(const std::string& name)
{
	return CheckHandleASyncLoad(m_sprites[name]) == FALSE;
}