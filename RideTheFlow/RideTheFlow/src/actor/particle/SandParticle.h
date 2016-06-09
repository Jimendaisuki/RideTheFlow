#pragma once

#include "Particle.h"
#include <vector>

class SandParticle :public Particle
{
public:
	SandParticle(const Vector3& position_, const Vector3& vec_);

	void OnUpdate() override;
	void Draw() const override;

private:
	//Ž²
	Vector3 up, front, left;
	//‰ñ“]
	Matrix4 rotmat;
};