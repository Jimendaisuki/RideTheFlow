#pragma once

#include "Particle.h"
#include "BreakCastle.h"
#include <vector>

class BreakCastleParticle :public Particle
{
public:
	//���f��ID�A�����A�V�X�e���̍��W�A���W�A�ړ�����*�ړ��ʁA������]X�A������]Y
	BreakCastleParticle(const MODEL_ID& id_, const BREAK_SELECT& break_, Vector3* parentPosition_,const Vector3& position_, const Vector3& vec_, float rotX_, float rotY_ , float scale_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//�����ɂ�����
	void TornadoBreak();
	//����ɂ�����
	void WindFlowBreak();
	//��C�C�ɂ�����
	void WindBallBreak();
	//�_���[�W
	void DamageBreak();

private:
	//����
	BREAK_SELECT breakSelect;
	//�Ǘ��҂ł���BreakCastle�̍��W
	Vector3* pParentPosition;
	//������̉�]��
	float rotX, rotY;
	//��]
	Matrix4 rotmat;
	//�ŏI�I�ȃ}�g���b�N�X
	Matrix4 mat;

	//����
	float rotXSpeed,rotYSpeed;
	float rotXAdd, rotYAdd;
	float risingSpeed;
	float tornadeRadius;
	float tornadeDegree;
	float tornadeAddRadius;
	float tornadeSpeed;
	Vector3 tornadeAddPosition;

	//����
	float flowRisingSpeed;
	float flowRotXSpeed, flowRotYSpeed;
	float flowRotXAdd, flowRotYAdd;
	Vector3 flowAddPosition;

	//��C�C
	float ballRotXSpeed, ballRotYSpeed;
};