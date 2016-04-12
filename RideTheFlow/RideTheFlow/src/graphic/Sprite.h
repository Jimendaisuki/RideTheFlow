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
	/// 初期化処理
	///</summary>
	void Initialize();

	///<summary>
	/// 通常画像の読み込み(アセット名)
	///</summary>
	void Load(const std::string& filename);
	///<summary>
	/// 分割画像の読み込み(アセット名、分割数、横と縦の分割数、1コマの大きさ)
	///</summary>
	void Load(const std::string& filename, int allnum, const Point& splitnum, const Point& size);
	///<summary>
	/// 通常画像の描画(アセット名、座標)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position);
	///<summary>
	/// 通常画像の描画(アセット名、座標、アルファ値)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, float alpha);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、拡大率)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、拡大率、回転率)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle);
	///<summary>
	/// 通常画像の描画(アセット名、座標、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, bool trans, bool turn);
	///<summary>
	/// 通常画像の描画(アセット名、座標、アルファ値、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, float alpha, bool trans, bool turn);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、拡大率、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、拡大率、回転率、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// 通常画像の描画(アセット名、座標、原点、アルファ値、拡大率、回転率、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// 通常画像の描画(アセット名、座標、表示矩形サイズ、原点、アルファ値、拡大率、回転率、透過、反転)
	///</summary>
	void Draw(const std::string& assetname, const Vector2& position, const Point& size, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、アルファ値)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、拡大率)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、アルファ値、拡大率)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、拡大率、回転率)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, float angle);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、アルファ値、拡大率、回転率)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, float angle);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、アルファ値、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, float alpha, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、拡大率、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、アルファ値、拡大率、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、拡大率、回転率、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、原点、アルファ値、拡大率、回転率、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);
	///<summary>
	/// 分割画像の描画(アセット名、座標、表示コマ番号、表示矩形サイズ、原点、アルファ値、拡大率、回転率、透過、反転)
	///</summary>
	void SplitDraw(const std::string& assetname, const Vector2& position, int frame, const Point& size, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn);

	///<summary>
	/// 指定の桁番目の表示コマ番号を取得する（数字、欲しい桁番目の表示コマ番号、最大桁数）
	///</summary>
	static int NumberFrame(int number, int digit, int maxdigit);

	bool IsASyncLoad(const std::string& name);

	int GetCount()
	{
		return static_cast<int>(m_sprites.size());
	}

	///<summary>
	/// 画像のサイズを取得する
	///</summary>
	Point GetSize(const std::string& assetname) const
	{
		Point size;
		GetGraphSize(m_sprites.at(assetname), &size.x, &size.y);
		return size;
	}

private:
	///<summary>
	/// ファイル名の'.'から後を取り除く
	///</summary>
	std::string Split(std::string filename);
	///<summary>
	/// 画像にアルファブレンド処理を施す
	///</summary>
	void AlphaBlend(float alpha);
	///<summary>
	/// 画像のブレンド処理をデフォルトにする
	///</summary>
	void DefaultBlend();

private:
	// 通常画像
	std::unordered_map<std::string, int> m_sprites;
	// 分割画像
	std::unordered_map<std::string, std::vector<int>> m_splitsprites;
	// 読み込んだ分割画像のコマ数
	std::unordered_map<std::string, Point> m_comma;
};