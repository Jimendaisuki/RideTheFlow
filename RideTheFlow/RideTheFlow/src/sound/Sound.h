#pragma once

#include <string>
#include <unordered_map>

class Sound
{
public:
	Sound();
	~Sound();

	///<summary>
	/// ����������
	///</summary>
	void Initialize();

	///<summary>
	/// BGM��ǂݍ���
	///</summary>
	void LoadBGM(const std::string& filename, float volume = 1.0f);
	///<summary>
	/// SE��ǂݍ���
	///</summary>
	void LoadSE(const std::string& filename, float volume = 1.0f);
	///<summary>
	/// BGM��炷
	///</summary>
	void PlayBGM(const std::string& assetname, int playtype);
	///<summary>
	/// SE��炷
	///</summary>
	void PlaySE(const std::string& assetname, int playtype);
	///<summary>
	/// BGM���~�߂�
	///</summary>
	void StopBGM();
	///<summary>
	/// SE���~�߂�
	///</summary>
	void StopSE(const std::string& assetname);

	///<summary>
	/// BGM�����Ă��邩�ǂ������ׂ�
	///</summary>
	bool IsPlayBGM();
	///<summary>
	/// SE�����Ă��邩�ǂ������ׂ�
	///</summary>
	bool IsPlaySE(const std::string& assetname);

	///<summary>
	/// �eBGM�̃{�����[����ݒ肷��
	///</summary>
	void SetBGMVolume(const std::string& assetname, float volume);
	///<summary>
	/// �eSE�̃{�����[����ݒ肷��
	///</summary>
	void SetSEVolume(const std::string& assetname, float volume);
	///<summary>
	/// �eBGM�̃{�����[�����󂯎��
	///</summary>
	float IsBGMVolume(const std::string& assetname);
	///<summary>
	/// �eSE�̃{�����[�����󂯎��
	///</summary>
	float IsSEVolume(const std::string& assetname);

	///<summary>
	/// �S�Ă�BGM�̃{�����[����ݒ肷��
	///</summary>
	void SetAllBGMVolume(float volume);
	///<summary>
	/// �S�Ă�SE�̃{�����[����ݒ肷��
	///</summary>
	void SetAllSEVolume(float volume);
	///<summary>
	/// �S�Ă�BGM�̃{�����[�����󂯎��
	///</summary>
	float IsAllBGMVolume();
	///<summary>
	/// �S�Ă�SE�̃{�����[�����󂯎��
	///</summary>
	float IsAllSEVolume();

	int GetCountBGM()
	{
		return static_cast<int>(m_BGMs.size());
	}
	int GetCountSE()
	{
		return static_cast<int>(m_SEs.size());
	}

	Sound(const Sound& other);
	Sound& operator = (const Sound& other);

private:
	std::string Split(const std::string& filename);

private:
	void SettingBGM(const std::string& assetname);

	void SettingSE(const std::string& assetname);

	std::unordered_map<std::string, int> m_BGMs;			// BGM�n���h��
	std::unordered_map<std::string, int> m_SEs;				// SE�n���h��
	std::unordered_map<std::string, float> m_BGM_Volumes;	// �eBGM�{�����[��
	std::unordered_map<std::string, float> m_SE_Volumes;	// �eSE�{�����[��
	float m_bgm_volume;										// �SBGM�{�����[��
	float m_se_volume;										// �SSE�{�����[��
};