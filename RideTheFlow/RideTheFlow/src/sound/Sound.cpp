#include "Sound.h"
#include "../game/WorkFolder.h"
#include "../Def.h"
#include "../math/Math.h"
#include <sstream>

Sound::Sound():
	m_bgm_volume(BGMVOLUME), m_se_volume(SEVOLUME)
{
	
}

Sound::~Sound()
{
	InitSoundMem();
}

// 初期化処理
void Sound::Initialize()
{
	InitSoundMem();
	m_BGMs.clear();
	m_SEs.clear();
}

// BGMを読み込む
void Sound::LoadBGM(const std::string& filename, float volume)
{
	m_BGMs[Split(filename)] = LoadSoundMem((WorkFolder::Name + filename).c_str());
	m_BGM_Volumes[Split(filename)] = volume;
	SettingBGM(Split(filename));
}

// SEを読み込む
void Sound::LoadSE(const std::string& filename, float volume)
{
	m_SEs[Split(filename)] = LoadSoundMem((WorkFolder::Name + filename).c_str());
	m_SE_Volumes[Split(filename)] = volume;
	SettingSE(Split(filename));
}

// ファイル名の'.'から後を取り除く
std::string Sound::Split(const std::string& filename)
{
	std::string assetname;
	std::getline(
		std::stringstream(filename),
		assetname,
		'.'
	);
	return assetname;
}

// BGMを鳴らす
void Sound::PlayBGM(const std::string& assetname, int playtype = DX_PLAYTYPE_BACK)
{
	WorkFolder::CheckName(assetname, m_BGMs);
	
	PlaySoundMem(m_BGMs[assetname], playtype);
}

// SEを鳴らす
void Sound::PlaySE(const std::string& assetname, int playtype)
{
	WorkFolder::CheckName(assetname, m_SEs);
	if (IsPlaySE(assetname) && playtype == DX_PLAYTYPE_LOOP)
		return;

	ChangeVolumeSoundMem((int)((m_se_volume * m_SE_Volumes[assetname]) * 255), m_SEs[assetname]);
	PlaySoundMem(m_SEs[assetname], playtype);
}

// BGMを止める
void Sound::StopBGM()
{
	for (auto i : m_BGMs)
	{
		StopSoundMem(i.second);
	}
}

// SEを止める
void Sound::StopSE(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_SEs);
	StopSoundMem(m_SEs[assetname]);
}

// BGMが鳴っているかどうか調べる
bool Sound::IsPlayBGM()
{
	for (auto i : m_BGMs)
	{
		if (CheckSoundMem(i.second))
		{
			return true;
		}
	}
	return false;
}

// SEが鳴っているかどうか調べる
bool Sound::IsPlaySE(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_SEs);
	return CheckSoundMem(m_SEs[assetname]) == 1;
}

// 各BGMのボリュームを設定する
void Sound::SetBGMVolume(const std::string& assetname, float volume)
{
	WorkFolder::CheckName(assetname, m_BGMs);
	m_BGM_Volumes[assetname] = volume;
	SettingBGM(assetname);
}

// 各SEのボリュームを設定する
void Sound::SetSEVolume(const std::string& assetname, float volume)
{
	WorkFolder::CheckName(assetname, m_SEs);
	m_SE_Volumes[assetname] = volume;
	SettingSE(assetname);
}

// 各BGMのボリュームを受け取る
float Sound::IsBGMVolume(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_BGMs);
	return m_BGM_Volumes[assetname];
}

// 各SEのボリュームを受け取る
float Sound::IsSEVolume(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_SEs);
	return m_SE_Volumes[assetname];
}

// 全てのBGMのボリュームを設定する
void Sound::SetAllBGMVolume(float volume)
{
	m_bgm_volume = volume;
	for (auto& i : m_BGMs)
		SettingBGM(i.first);
	m_bgm_volume = Math::Clamp(m_bgm_volume, 0.0f, 1.0f);
}

// 全てのSEのボリュームを設定する
void Sound::SetAllSEVolume(float volume)
{
	m_se_volume = volume;
	for (auto& i : m_SEs)
		SettingSE(i.first);
	m_se_volume = Math::Clamp(m_se_volume, 0.0f, 1.0f);
}

// 全てのBGMのボリュームを受け取る
float Sound::IsAllBGMVolume()
{
	return m_bgm_volume;
}

// 全てのSEのボリュームを受け取る
float Sound::IsAllSEVolume()
{
	return m_se_volume;
}

void Sound::SettingBGM(const std::string& assetname)
{
	ChangeVolumeSoundMem((int)((m_bgm_volume * m_BGM_Volumes[assetname]) * 255), m_BGMs[assetname]);
}

void Sound::SettingSE(const std::string& assetname)
{
	ChangeVolumeSoundMem((int)((m_se_volume * m_SE_Volumes[assetname]) * 255), m_SEs[assetname]);
}