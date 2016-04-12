#pragma once

#include <unordered_map>
class Model;

class Anime
{
public:
	Anime(Model& model);
	~Anime() = default;

	///<summary>
	/// �g�p����A�j���[�V�������A�^�b�`����
	///</summary>
	void AttachAnime(const std::string& modelname, int animestate);
	///<summary>
	/// �g�p���Ȃ��A�j���[�V��������������
	///</summary>
	void RemoveAnime(const std::string& modelname, int animestate);
	///<summary>
	/// �A�j���[�V�����̃t���[�����X�V����
	///</summary>
	void PlayAnime(const std::string& modelname, int animestate, float animetime);
	///<summary>
	/// �A�j���[�V�����̑����Ԃ��擾����
	///</summary>
	float GetTotalTime(const std::string& modelname, int animestate);
	///<summary>
	/// �������Z�̐ݒ�����Z�b�g����(���A���^�C���������Z�ݒ�̂�)
	///</summary>
	void PhysicsReset(const std::string& modelname);
	///<summary>
	/// �������Z���s���i���A���^�C���������Z�ݒ�̂݁j
	///</summary>
	void PhysicsUpdate(const std::string& modelname, float time);

	Anime(const Anime& other);
	Anime& operator = (const Anime& other);

private:
	std::unordered_map<std::string, std::unordered_map<int, int>> m_animes;

	Model& m_model;
};