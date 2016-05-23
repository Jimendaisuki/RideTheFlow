#pragma once

#include "Particle.h"
#include <vector>
#include "WindFlow.h"

class WindFlowParticle:public Particle
{
public:
	//(�V�X�e���{��,�_�b�V�����̋O��,�������鍂��)
	WindFlowParticle(WindFlow& windflow_,const std::vector<Vector3>& dashPositions_, float positionHeight_);

	void OnUpdate() override;
	void Draw() const override;

private:
	WindFlow& windFlow;
	//�v���C���[�̃_�b�V���̋O��
	std::vector<Vector3> dashPositions;
	//�ʒu�����炵�ĕ�����������
	Vector3 randomPosition;

	//�p�[�e�B�N�����������[���h���Y�l
	float positionHeight;

	//��]
	Vector3 rotate;
};