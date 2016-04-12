#pragma once

#include <unordered_map>
class Model;

class Anime
{
public:
	Anime(Model& model);
	~Anime() = default;

	///<summary>
	/// 使用するアニメーションをアタッチする
	///</summary>
	void AttachAnime(const std::string& modelname, int animestate);
	///<summary>
	/// 使用しないアニメーションを除去する
	///</summary>
	void RemoveAnime(const std::string& modelname, int animestate);
	///<summary>
	/// アニメーションのフレームを更新する
	///</summary>
	void PlayAnime(const std::string& modelname, int animestate, float animetime);
	///<summary>
	/// アニメーションの総時間を取得する
	///</summary>
	float GetTotalTime(const std::string& modelname, int animestate);
	///<summary>
	/// 物理演算の設定をリセットする(リアルタイム物理演算設定のみ)
	///</summary>
	void PhysicsReset(const std::string& modelname);
	///<summary>
	/// 物理演算を行う（リアルタイム物理演算設定のみ）
	///</summary>
	void PhysicsUpdate(const std::string& modelname, float time);

	Anime(const Anime& other);
	Anime& operator = (const Anime& other);

private:
	std::unordered_map<std::string, std::unordered_map<int, int>> m_animes;

	Model& m_model;
};