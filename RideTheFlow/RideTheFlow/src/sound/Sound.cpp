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

// ����������
void Sound::Initialize()
{
	InitSoundMem();
	m_BGMs.clear();
	m_SEs.clear();
}

// BGM��ǂݍ���
void Sound::LoadBGM(const std::string& filename, float volume)
{
	m_BGMs[Split(filename)] = LoadSoundMem((WorkFolder::Name + filename).c_str());
	m_BGM_Volumes[Split(filename)] = volume;
	SettingBGM(Split(filename));
}

// SE��ǂݍ���
void Sound::LoadSE(const std::string& filename, float volume)
{
	m_SEs[Split(filename)] = LoadSoundMem((WorkFolder::Name + filename).c_str());
	m_SE_Volumes[Split(filename)] = volume;
	SettingSE(Split(filename));
}

// �t�@�C������'.'��������菜��
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

// BGM��炷
void Sound::PlayBGM(const std::string& assetname, int playtype = DX_PLAYTYPE_BACK)
{
	WorkFolder::CheckName(assetname, m_BGMs);
	
	PlaySoundMem(m_BGMs[assetname], playtype);
}

// SE��炷
void Sound::PlaySE(const std::string& assetname, int playtype)
{
	WorkFolder::CheckName(assetname, m_SEs);
	if (IsPlaySE(assetname) && playtype == DX_PLAYTYPE_LOOP)
		return;

	ChangeVolumeSoundMem((int)((m_se_volume * m_SE_Volumes[assetname]) * 255), m_SEs[assetname]);
	PlaySoundMem(m_SEs[assetname], playtype);
}

// BGM���~�߂�
void Sound::StopBGM()
{
	for (auto i : m_BGMs)
	{
		StopSoundMem(i.second);
	}
}

// SE���~�߂�
void Sound::StopSE(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_SEs);
	StopSoundMem(m_SEs[assetname]);
}

// BGM�����Ă��邩�ǂ������ׂ�
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

// SE�����Ă��邩�ǂ������ׂ�
bool Sound::IsPlaySE(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_SEs);
	return CheckSoundMem(m_SEs[assetname]) == 1;
}

// �eBGM�̃{�����[����ݒ肷��
void Sound::SetBGMVolume(const std::string& assetname, float volume)
{
	WorkFolder::CheckName(assetname, m_BGMs);
	m_BGM_Volumes[assetname] = volume;
	SettingBGM(assetname);
}

// �eSE�̃{�����[����ݒ肷��
void Sound::SetSEVolume(const std::string& assetname, float volume)
{
	WorkFolder::CheckName(assetname, m_SEs);
	m_SE_Volumes[assetname] = volume;
	SettingSE(assetname);
}

// �eBGM�̃{�����[�����󂯎��
float Sound::IsBGMVolume(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_BGMs);
	return m_BGM_Volumes[assetname];
}

// �eSE�̃{�����[�����󂯎��
float Sound::IsSEVolume(const std::string& assetname)
{
	WorkFolder::CheckName(assetname, m_SEs);
	return m_SE_Volumes[assetname];
}

// �S�Ă�BGM�̃{�����[����ݒ肷��
void Sound::SetAllBGMVolume(float volume)
{
	m_bgm_volume = volume;
	for (auto& i : m_BGMs)
		SettingBGM(i.first);
	m_bgm_volume = Math::Clamp(m_bgm_volume, 0.0f, 1.0f);
}

// �S�Ă�SE�̃{�����[����ݒ肷��
void Sound::SetAllSEVolume(float volume)
{
	m_se_volume = volume;
	for (auto& i : m_SEs)
		SettingSE(i.first);
	m_se_volume = Math::Clamp(m_se_volume, 0.0f, 1.0f);
}

// �S�Ă�BGM�̃{�����[�����󂯎��
float Sound::IsAllBGMVolume()
{
	return m_bgm_volume;
}

// �S�Ă�SE�̃{�����[�����󂯎��
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