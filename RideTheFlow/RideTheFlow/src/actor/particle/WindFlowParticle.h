#pragma once

#include "Particle.h"
#include <vector>

class WindFlowParticle:public Particle
{
public:
	WindFlowParticle(const std::vector<Vector3>& dashPositions_, float positionHeight_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//�v���C���[�̃_�b�V���̋O��
	std::vector<Vector3> dashPositions;
	//�ʒu�����炵�ĕ�����������
	Vector3 randomPosition;

	//�p�[�e�B�N�����������[���h���Y�l
	float positionHeight;

	//��]
	Vector3 rotate;
};