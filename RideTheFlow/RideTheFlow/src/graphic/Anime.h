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
	/// �g�p����A�j���[�V�������A�^�b�`����
	///</summary>
	void AttachAnime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id);
	///<summary>
	/// �g�p���Ȃ��A�j���[�V��������������
	///</summary>
	void RemoveAnime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id);
	///<summary>
	/// �A�j���[�V�����̃t���[�����X�V����
	///</summary>
	void PlayAnime(const ANIME_ID& a_id, int animestate, float animetime, const MODEL_ID& m_id);
	///<summary>
	/// �A�j���[�V�����̑����Ԃ��擾����
	///</summary>
	float GetTotalTime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id);
	///<summary>
	/// �������Z�̐ݒ�����Z�b�g����(���A���^�C���������Z�ݒ�̂�)
	///</summary>
	void PhysicsReset(const ANIME_ID& a_id, const MODEL_ID& m_id);
	///<summary>
	/// �������Z���s���i���A���^�C���������Z�ݒ�̂݁j
	///</summary>
	void PhysicsUpdate(const ANIME_ID& a_id, float time, const MODEL_ID& m_id);

	Anime(const Anime& other);
	Anime& operator = (const Anime& other);

private:
	std::unordered_map<ANIME_ID, std::unordered_map<int, int>> m_animes;
};