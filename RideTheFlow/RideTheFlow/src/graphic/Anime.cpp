#include "Anime.h"
#include "Model.h"

void Anime::AttachAnime(const std::string& modelname, int animestate)
{
	m_animes[modelname][animestate] = MV1AttachAnim(Model::GetInstance().GetHandle(modelname), animestate, -1, FALSE);
	if (m_animes[modelname][animestate] == -1)
		throw std::string(modelname + "のアタッチに失敗しました\n");
}

void Anime::RemoveAnime(const std::string& modelname, int animestate)
{
	MV1DetachAnim(Model::GetInstance().GetHandle(modelname), m_animes[modelname][animestate]);
}

void Anime::PlayAnime(const std::string& modelname, int animestate, float animetime)
{
	MV1SetAttachAnimTime(Model::GetInstance().GetHandle(modelname), m_animes[modelname][animestate], animetime);
}

float Anime::GetTotalTime(const std::string& modelname, int animestate)
{
	return MV1GetAttachAnimTotalTime(Model::GetInstance().GetHandle(modelname), m_animes[modelname][animestate]);
}

void Anime::PhysicsReset(const std::string& modelname)
{
	MV1PhysicsResetState(Model::GetInstance().GetHandle(modelname));
}

void Anime::PhysicsUpdate(const std::string& modelname, float time)
{
	MV1PhysicsCalculation(Model::GetInstance().GetHandle(modelname), time);
}