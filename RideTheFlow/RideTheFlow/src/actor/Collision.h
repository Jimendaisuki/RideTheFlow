#pragma once
#include "ID.h"
#include <memory>
#include "../math/Vector3.h"

//�����蔻��̃p�����[�^
struct CollisionParameter{
	bool	colFlag = false;		//���������ǂ����̃t���O		//�G����̍U���i㩁j���H
	Vector3 colPos = Vector3::Zero;
};

// �J�v�Z��
struct  Capsule{
	Vector3	startPos;			// �J�v�Z���̎n�_
	Vector3 endPos;				// �J�v�Z���̏I�_
	float	radius;				// ���a
};