#include "Particle.h"

#include "../../time/Time.h"

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
	lifeParam.lifeTime += Time::DeltaTime;
	if (lifeParam.lifeTime > lifeParam.lifeTimeLimit)
		lifeParam.isDead = true;
	else
	{
		moveParam.pos += moveParam.vec * moveParam.speed *  Time::DeltaTime;
		moveParam.speed += moveParam.addSpeed * Time::DeltaTime;
		drawParam.size += drawParam.addSize * Time::DeltaTime;
		drawParam.alpha += drawParam.addAlpha * Time::DeltaTime;
	}
}

void Particle::Draw() const
{
	if (drawParam.blendMode == BLEND_MODE::NoBlend)
		Model::GetInstance().Draw2D(drawParam.drawID, moveParam.pos, 0, drawParam.size, drawParam.billboardOrigin, 0);
	else
		Model::GetInstance().Draw2DBlend(drawParam.drawID, moveParam.pos, 0, drawParam.size, drawParam.billboardOrigin, 0, drawParam.blendMode, drawParam.alpha);
}

bool Particle::GetIsDead()
{
	return lifeParam.isDead;
}