#pragma once
#include "../Actor.h"
#include "ParticlePtr.h"
#include <list>

//�p�[�e�B�N���V�X�e���́A�ݒ肷�ׂ����l�\����
struct ParticleSystemParameter
{
	//���o�̒��S�A��ƂȂ�ʒu
	Vector3 position;

	//���o�Ԋu(�b)
	float intervalSec;
	//��x�ɓ������o���鐔
	int sameEmissiveNum;

	//��������
	float lifeTimeLimit;
	//�������ǂ���
	bool isDead;
	//�V�X�e���������ɂP�x���o���s�����H
	bool trigger;
};

class ParticleSystem
{
public:
	///<summary>
	///�p�[�e�B�N���̐����A��čX�V�E�`��Ǘ��N���X
	///</summary>
	ParticleSystem();
	~ParticleSystem();

	//�ۊǂ��Ă���p�[�e�B�N�����X�V
	void UpdateParticles();
	//�ۊǂ��Ă���p�[�e�B�N����`��
	void DrawParticles() const;

	//�p�[�e�B�N���̐������@���L�q�i�������o�͏���ɍs���邽�߁A�P�s��ok�j
	virtual void Emissive() = 0;

	//�p�[�e�B�N����ǉ�
	void AddParticle(ParticlePtr particle);

	//����ł���p�[�e�B�N�����폜
	void RemoveDeadParticle();

	//�p�[�e�B�N���V�X�e�����I�����Ă��邩�H
	bool IsDeadSystem();

	ParticleSystemParameter GetPSParemeter()
	{
		return ps_parameter;
	}

	//�c��̐������Ԃ�Ԃ�
	float GetLifeTimeSub()
	{
		return ps_parameter.lifeTimeLimit - lifeTime;
	}

protected:
	//�p�[�e�B�N����ۊ�
	std::list<ParticlePtr> particles;

	//�����v���p
	float lifeTime;
	//���o�v���p
	float emissiveTimer;
	//�������o�����t���O
	bool isTriggerEnd;

	ParticleSystemParameter ps_parameter;
};