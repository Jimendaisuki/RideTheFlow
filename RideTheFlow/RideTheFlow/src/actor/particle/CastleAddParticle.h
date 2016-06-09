#pragma once

#include "Particle.h"
#include <vector>

class CastleAddParticle :public Particle
{
public:
	CastleAddParticle(const Vector3& position_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//������̉�]��
	float xrot, yrot;
	//��]
	Matrix4 rotmat;
	//�ŏI�I�ȃ}�g���b�N�X
	Matrix4 mat;

	float addAlpha;
	float rotationSpeed;
	float addSizeSpeed;
	float timer;
};