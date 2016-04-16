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
	void AttachAnime(const MODEL_ID& id, int animestate);
	///<summary>
	/// 使用しないアニメーションを除去する
	///</summary>
	void RemoveAnime(const MODEL_ID& id, int animestate);
	///<summary>
	/// アニメーションのフレームを更新する
	///</summary>
	void PlayAnime(const MODEL_ID& id, int animestate, float animetime);
	///<summary>
	/// アニメーションの総時間を取得する
	///</summary>
	float GetTotalTime(const MODEL_ID& id, int animestate);
	///<summary>
	/// 物理演算の設定をリセットする(リアルタイム物理演算設定のみ)
	///</summary>
	void PhysicsReset(const MODEL_ID& id);
	///<summary>
	/// 物理演算を行う（リアルタイム物理演算設定のみ）
	///</summary>
	void PhysicsUpdate(const MODEL_ID& id, float time);

	Anime(const Anime& other);
	Anime& operator = (const Anime& other);

private:
	std::unordered_map<MODEL_ID, std::unordered_map<int, int>> m_animes;
};