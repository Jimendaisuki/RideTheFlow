#pragma once

#include "Particle.h"
#include <vector>
#include "../tornado/Tornado.h"

class TornadoParticle :public Particle
{
public:
	TornadoParticle(Vector3& position_, std::weak_ptr<Tornado> tornade_);

	void OnUpdate() override;
	void Draw() const override;

private:
	std::weak_ptr<Tornado> tornade;
	Vector3 tornadePos;
	Vector3 tornadeMove;
	float tornadeAddRadius;
	float tornadeRadius;
	float tornadeSpeed;
	float tornadeDegree;
	float risingSpeed;
	float risingAddSpeed;

	float scale;
	Vector3 position;
	Vector3 rotate;
	Vector3 up, front, left;
	Matrix4 mat;

	//âÒì]Ç…ÇÊÇ¡Çƒâ¡Ç¶ÇÁÇÍÇÈç¿ïWó 
	Vector3 tornadeAddPosition;
	float timer;
	int drawFrame;
};