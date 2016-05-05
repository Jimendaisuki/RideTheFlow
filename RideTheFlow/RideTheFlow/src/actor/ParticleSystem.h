#pragma once
#include "Actor.h"
#include <vector>

enum PARTICLE_SHAPE
{
	BEGIN,
	SPHERE,
	HALF_SPHERE,
	BOX,
	CORN,
	END
};

class ParticleSystem :public Actor
{
public:
	class Particle
	{
	public:
		Particle(
			const Vector3& pos_,
			const Vector3& vec_ = Vector3::One,
			float life_ = 1.0f,
			float speed_ = 1.0f,
			float size_ = 1.0f,
			float alpha_ = 255.0f,
			float addSpeed_ = 0.0f,
			float addSize_ = 0.0f,
			float addAlpha_ = 0.0f);
		void Initialize(
			const Vector3& pos_ , 
			const Vector3& vec_ = Vector3::One,
			float speed_ = 1.0f,
			float size_ = 1.0f,
			float alpha_ = 255.0f,
			float addSpeed_ = 0.0f,
			float addSize_ = 0.0f,
			float addAlpha_ = 0.0f);
		void Update();
		void Draw(const MODEL_ID& drawID, Vector2 origin = Vector2::Zero, const int& blend_mode = BLEND_MODE::NoBlend) const;
		bool GetIsDead();
	private:
		//�p�[�e�B�N������
		float lifeTime;
		float lifeTimeLimit;
		bool isDead;
		//���W
		Vector3 pos;
		//�ړ�����
		Vector3 vec;
		//�e��
		float speed;
		//�e���x�ω���
		float addSpeed;
		//�摜�g�嗦
		float size;
		//�摜�g�嗦�ω���
		float addSize;
		//�A���t�@�l
		float alpha;
		//�A���t�@�l�ω���
		float addAlpha;
	};

public:
	///<summary>
	///����A�������͔�����ɕ��o����p�[�e�B�N���𐶐����܂��B
	///</summary>
	ParticleSystem(
		//���[���h
		IWorld& world,
		//�`�悷��2D�摜��ID
		const MODEL_ID& drawID_,
		//���o�Ԋu�i�b�j
		float intervalSec_,
		//�������ː�
		int sameEmissiveNum_,
		//��������
		float lifeTimeLimit_,
		//���o�n�_
		const Vector3& basePos_,
		//true:����Afalse:������
		bool isShpere,
		//�������x
		float initSpeed_ = 1.0f,
		//�����T�C�Y
		float initSize_ = 1.0f,
		//�����A���t�@�l
		float initAlpha_ = 255.0f,
		//�摜���S�ʒu
		const Vector2& billboardOrigin_ = Vector2::Zero,
		//���x������
		float addSpeed_ = 0.0f,
		//�T�C�Y������
		float addSize_ = 0.0f,
		//�A���t�@�l������
		float addAlpha_ = 0.0f,
		//�u�����h
		int blendMode_ = BLEND_MODE::NoBlend
		);
	~ParticleSystem();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//==============����===============//
	//�p�[�e�B�N����ۊ�
	std::vector<Particle> particles;
	//���o����`��
	PARTICLE_SHAPE shape;
	//�`�悷��摜
	MODEL_ID drawID;
	//���o�Ԋu(�b)
	float intervalSec;
	//��x�ɕ��o���鐔
	int sameEmissiveNum;

	//�����v���p
	float lifeTime;
	//��������
	float lifeTimeLimit;

	//�p�[�e�B�N���ɗ^�������
	float particleLifeTimeLimit;

	//�摜���S�ʒu
	Vector2 billboardOrigin;
	//���o�̒��S�A��ƂȂ�ʒu
	Vector3 basePos;

	//�e����
	float initSpeed;
	//�摜�g�嗦
	float initSize;
	//�A���t�@�l
	float initAlpha;

	//�e���x�ω���
	float addSpeed;
	//�摜�g�嗦�ω���
	float addSize;
	//�A���t�@�l�ω���
	float addAlpha;

	//�u�����h���[�h
	int blendMode;
	
	//�^�C�}�[
	float emissiveTimer;

	//==============BOX�ACORN����===============//
	//���o��������̊
	Vector3 vec;

	//==============BOX===============//
	//���o���锠�̑傫��
	Vector3 boxSize;

};