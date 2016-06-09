#pragma once

#include "Particle.h"
#include <vector>
#include "../tornado/Tornado.h"

class TornadoParticle :public Particle
{
public:
	TornadoParticle(std::weak_ptr<Tornado> tornade_,float radius);

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

	//âÒì]Ç…ÇÊÇ¡Çƒâ¡Ç¶ÇÁÇÍÇÈç¿ïWó 
	Vector3 tornadeAddPosition;

	Vector3 position;
	Vector3 up, front, left;
	Matrix4 rotmat;

	//ï`âÊÇ∑ÇÈÉRÉ}
	int frame;

};