#pragma once

#include <string>
#include <unordered_map>

class Sound
{
public:
	Sound();
	~Sound();

	///<summary>
	/// 初期化処理
	///</summary>
	void Initialize();

	///<summary>
	/// BGMを読み込む
	///</summary>
	void LoadBGM(const std::string& filename, float volume = 1.0f);
	///<summary>
	/// SEを読み込む
	///</summary>
	void LoadSE(const std::string& filename, float volume = 1.0f);
	///<summary>
	/// BGMを鳴らす
	///</summary>
	void PlayBGM(const std::string& assetname, int playtype);
	///<summary>
	/// SEを鳴らす
	///</summary>
	void PlaySE(const std::string& assetname, int playtype);
	///<summary>
	/// BGMを止める
	///</summary>
	void StopBGM();
	///<summary>
	/// SEを止める
	///</summary>
	void StopSE(const std::string& assetname);

	///<summary>
	/// BGMが鳴っているかどうか調べる
	///</summary>
	bool IsPlayBGM();
	///<summary>
	/// SEが鳴っているかどうか調べる
	///</summary>
	bool IsPlaySE(const std::string& assetname);

	///<summary>
	/// 各BGMのボリュームを設定する
	///</summary>
	void SetBGMVolume(const std::string& assetname, float volume);
	///<summary>
	/// 各SEのボリュームを設定する
	///</summary>
	void SetSEVolume(const std::string& assetname, float volume);
	///<summary>
	/// 各BGMのボリュームを受け取る
	///</summary>
	float IsBGMVolume(const std::string& assetname);
	///<summary>
	/// 各SEのボリュームを受け取る
	///</summary>
	float IsSEVolume(const std::string& assetname);

	///<summary>
	/// 全てのBGMのボリュームを設定する
	///</summary>
	void SetAllBGMVolume(float volume);
	///<summary>
	/// 全てのSEのボリュームを設定する
	///</summary>
	void SetAllSEVolume(float volume);
	///<summary>
	/// 全てのBGMのボリュームを受け取る
	///</summary>
	float IsAllBGMVolume();
	///<summary>
	/// 全てのSEのボリュームを受け取る
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

	std::unordered_map<std::string, int> m_BGMs;			// BGMハンドル
	std::unordered_map<std::string, int> m_SEs;				// SEハンドル
	std::unordered_map<std::string, float> m_BGM_Volumes;	// 各BGMボリューム
	std::unordered_map<std::string, float> m_SE_Volumes;	// 各SEボリューム
	float m_bgm_volume;										// 全BGMボリューム
	float m_se_volume;										// 全SEボリューム
};