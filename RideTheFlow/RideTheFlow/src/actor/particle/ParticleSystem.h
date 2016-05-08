#pragma once
#include "../Actor.h"
#include "ParticlePtr.h"

#include <list>

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
		//true:������Afalse:����
		bool isHalfShpere,
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
	///<summary>
	///����ɕ��o����p�[�e�B�N���𐶐����܂��B
	///</summary>
	ParticleSystem(
		IWorld& world,
		const MODEL_ID& drawID_,
		float intervalSec_,
		int sameEmissiveNum_,
		float lifeTimeLimit_,
		float particleLifeTimeLimit_,
		const Vector3& basePos_,
		const Vector3& emissiveVec_ = Vector3::One,
		const Vector3& boxSize_ = Vector3::One,
		float initSpeed_ = 1.0f,
		float initSize_ = 1.0f,
		float initAlpha_ = 255.0f,
		const Vector2& billboardOrigin_ = Vector2::Zero,
		float addSpeed_ = 0.0f,
		float addSize_ = 0.0f,
		float addAlpha_ = 0.0f,
		int blendMode_ = BLEND_MODE::NoBlend
		);
	~ParticleSystem();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

	void Add(ParticlePtr particle);
	void Remove();

private:
	//==============����===============//
	//�p�[�e�B�N����ۊ�
	std::list<ParticlePtr> particles;

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
	//���o�̒��S�A��ƂȂ�ʒu
	Vector3 basePos;
	//�摜���S�ʒu
	Vector2 billboardOrigin;

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
	Vector3 emissiveVec;

	//==============BOX===============//
	//���o���锠�̑傫��
	Vector3 boxSize;

};