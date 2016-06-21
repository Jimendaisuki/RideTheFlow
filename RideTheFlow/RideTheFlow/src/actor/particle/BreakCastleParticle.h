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
	//軸周りの回転量
	float rotX, rotY;
	//回転速度
	float rotationSpeed;
	//回転
	Matrix4 rotmat;
	//最終的なマトリックス
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