#pragma once

#include "Particle.h"
#include <vector>

class BreakCastleParticle :public Particle
{
public:
	BreakCastleParticle(const MODEL_ID& id_, const Vector3& position_, float rotX_, float rotY_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//������̉�]��
	float rotX, rotY;
	//��]���x
	float rotationSpeed;
	//��]
	Matrix4 rotmat;
	//�ŏI�I�ȃ}�g���b�N�X
	Matrix4 mat;

	float rotXSpeed,rotYSpeed;
	float rotXAdd, rotYAdd;
	float risingSpeed;
	float tornadeRadius;
	float tornadeDegree;
	float tornadeAddRadius;
	float tornadeSpeed;
	Vector3 tornadeAddPosition;
};