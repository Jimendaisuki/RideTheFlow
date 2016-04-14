#pragma once

#include <unordered_map>
#include "../actor/ID.h"

class Anime
{
private:
	Anime() = default;
	~Anime() = default;

public:
	static Anime &GetInstance(){
		static Anime a;
		return a;
	}

	///<summary>
	/// 使用するアニメーションをアタッチする
	///</summary>
	void AttachAnime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id);
	///<summary>
	/// 使用しないアニメーションを除去する
	///</summary>
	void RemoveAnime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id);
	///<summary>
	/// アニメーションのフレームを更新する
	///</summary>
	void PlayAnime(const ANIME_ID& a_id, int animestate, float animetime, const MODEL_ID& m_id);
	///<summary>
	/// アニメーションの総時間を取得する
	///</summary>
	float GetTotalTime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id);
	///<summary>
	/// 物理演算の設定をリセットする(リアルタイム物理演算設定のみ)
	///</summary>
	void PhysicsReset(const ANIME_ID& a_id, const MODEL_ID& m_id);
	///<summary>
	/// 物理演算を行う（リアルタイム物理演算設定のみ）
	///</summary>
	void PhysicsUpdate(const ANIME_ID& a_id, float time, const MODEL_ID& m_id);

	Anime(const Anime& other);
	Anime& operator = (const Anime& other);

private:
	std::unordered_map<ANIME_ID, std::unordered_map<int, int>> m_animes;
};