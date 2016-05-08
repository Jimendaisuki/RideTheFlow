#pragma once

#include "../../math/Vector2.h"
#include "../../math/Vector3.h"
#include "../../graphic/Model.h"

struct ParticleLifeParameter
{
	//��������
	float lifeTime;
	//�p�[�e�B�N������
	float lifeTimeLimit;
	//�������}�������H
	bool isDead;
};

struct ParticleMoveParameter
{
	//���W
	Vector3 pos;
	//�ړ�����
	Vector3 vec;
	//�e��
	float speed;
	//�e���x�ω���
	float addSpeed;
};

struct ParticleDrawParameter
{
	//�`�悷�郂�f��ID
	MODEL_ID drawID;
	//�g�嗦
	float size;
	//�g�嗦�ω���
	float addSize;
	//�A���t�@�l
	float alpha;
	//�A���t�@�l�ω���
	float addAlpha;
	//�u�����h���[�h
	int blendMode;
	//�摜���S�ʒu
	Vector2 billboardOrigin;
};

class Particle
{
public:
	Particle(
		const MODEL_ID& id_,
		float lifeLimit_,
		const Vector3& pos_,
		const Vector3& vec_ = Vector3::Zero,
		float speed_ = 1.0f,
		float addSpeed_ = 0.0f,
		float size_ = 1.0f,
		float addSize_ = 0.0f,
		float alpha_ = 255.0f,
		float addAlpha_ = 0.0f,
		int blendMode_ = BLEND_MODE::NoBlend,
		const Vector2& origin_ = Vector2::Zero);

	void Update();
	void Draw() const;
	bool GetIsDead();

private:
	ParticleLifeParameter lifeParam;
	ParticleMoveParameter moveParam;
	ParticleDrawParameter drawParam;
};