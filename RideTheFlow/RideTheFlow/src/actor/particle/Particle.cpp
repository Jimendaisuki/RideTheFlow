#include "Particle.h"

#include "../../time/Time.h"

Particle::Particle()
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 1.0f;
	lifeParam.isDead = false;

	moveParam.pos = Vector3::Zero;
	moveParam.vec = Vector3::Zero;
	moveParam.speed = 1.0f;
	moveParam.addSpeed = 0.0f;

	drawParam.drawID = MODEL_ID::WIND_2D;
	drawParam.size = 1.0f;
	drawParam.addSize = 0.0f;
	drawParam.alpha = 255.0f;
	drawParam.addAlpha = 0.0f;
	drawParam.blendMode = BLEND_MODE::NoBlend;
	drawParam.billboardOrigin = Vector2::Zero;
}


Particle::Particle(
	const MODEL_ID& id_,
	float lifeLimit_,
	const Vector3& pos_,
	const Vector3& vec_,
	float speed_,
	float addSpeed_,
	float size_,
	float addSize_,
	float alpha_,
	float addAlpha_,
	int blendMode_,
	const Vector2& origin_)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = lifeLimit_;
	lifeParam.isDead = false;

	moveParam.pos = pos_;
	moveParam.vec = vec_;
	moveParam.speed = speed_;
	moveParam.addSpeed = addSpeed_;

	drawParam.drawID = id_;
	drawParam.size = size_;
	drawParam.addSize = addSize_;
	drawParam.alpha = alpha_;
	drawParam.addAlpha = addAlpha_;
	drawParam.blendMode = blendMode_;
	drawParam.billboardOrigin = origin_;
}

void Particle::Update()
{
	//Žõ–½ŒvŽZ
	lifeParam.lifeTime += Time::GetInstance().deltaTime();
	if (lifeParam.lifeTime > lifeParam.lifeTimeLimit)
		lifeParam.isDead = true;

	OnUpdate();
}

bool Particle::GetIsDead()
{
	return lifeParam.isDead;
}