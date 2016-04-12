#include "Anime.h"
#include "Model.h"

Anime::Anime(Model& model)
	:m_model(model){}

void Anime::AttachAnime(const std::string& modelname, int animestate)
{
	m_animes[modelname][animestate] = MV1AttachAnim(m_model.GetHandle(modelname), animestate, -1, FALSE);
	if (m_animes[modelname][animestate] == -1)
		throw std::string(modelname + "のアタッチに失敗しました\n");
}

void Anime::RemoveAnime(const std::string& modelname, int animestate)
{
	MV1DetachAnim(m_model.GetHandle(modelname), m_animes[modelname][animestate]);
}

void Anime::PlayAnime(const std::string& modelname, int animestate, float animetime)
{
	MV1SetAttachAnimTime(m_model.GetHandle(modelname), m_animes[modelname][animestate], animetime);
}

float Anime::GetTotalTime(const std::string& modelname, int animestate)
{
	return MV1GetAttachAnimTotalTime(m_model.GetHandle(modelname), m_animes[modelname][animestate]);
}

void Anime::PhysicsReset(const std::string& modelname)
{
	MV1PhysicsResetState(m_model.GetHandle(modelname));
}

void Anime::PhysicsUpdate(const std::string& modelname, float time)
{
	MV1PhysicsCalculation(m_model.GetHandle(modelname), time);
}