#include "Anime.h"
#include "Model.h"

void Anime::AttachAnime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id)
{
	m_animes[a_id][animestate] = MV1AttachAnim(Model::GetInstance().GetHandle(m_id), animestate, -1, FALSE);
	if (m_animes[a_id][animestate] == -1)
		throw std::string("アタッチに失敗しました\n");
}

void Anime::RemoveAnime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id)
{
	MV1DetachAnim(Model::GetInstance().GetHandle(m_id), m_animes[a_id][animestate]);
}

void Anime::PlayAnime(const ANIME_ID& a_id, int animestate, float animetime, const MODEL_ID& m_id)
{
	MV1SetAttachAnimTime(Model::GetInstance().GetHandle(m_id), m_animes[a_id][animestate], animetime);
}

float Anime::GetTotalTime(const ANIME_ID& a_id, int animestate, const MODEL_ID& m_id)
{
	return MV1GetAttachAnimTotalTime(Model::GetInstance().GetHandle(m_id), m_animes[a_id][animestate]);
}

void Anime::PhysicsReset(const ANIME_ID& a_id, const MODEL_ID& m_id)
{
	MV1PhysicsResetState(Model::GetInstance().GetHandle(m_id));
}

void Anime::PhysicsUpdate(const ANIME_ID& a_id, float time, const MODEL_ID& m_id)
{
	MV1PhysicsCalculation(Model::GetInstance().GetHandle(m_id), time);
}