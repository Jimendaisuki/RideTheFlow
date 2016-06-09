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
	//軸周りの回転量
	float xrot, yrot;
	//回転
	Matrix4 rotmat;
	//最終的なマトリックス
	Matrix4 mat;

	float addAlpha;
	float rotationSpeed;
	float addSizeSpeed;
	float timer;
};