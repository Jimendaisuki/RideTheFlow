#include "ParticleSystem.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../time/Time.h"
#include "../graphic/TextDraw.h"
#include "../math/Math.h"
#include "../game/Random.h"

ParticleSystem::Particle::Particle()
{

}

void ParticleSystem::Particle::Initialize(Vector3 vec_, float speed_, float size_, float alpha_, float addSpeed_, float addSize_, float addAlpha_)
{


}

void ParticleSystem::Particle::Update()
{

}

void ParticleSystem::Particle::Draw(const MODEL_ID& drawID, Vector2 origin, const int& blend_mode) const
{
	if (blend_mode == BLEND_MODE::NoBlend)
		Model::GetInstance().Draw2D(drawID, pos, 0, size, origin, 0);
	else
		Model::GetInstance().Draw2DBlend(drawID, pos, 0, size, origin, 0, blend_mode, alpha);
}

ParticleSystem::ParticleSystem(
	IWorld& world,
	const MODEL_ID& drawID_,
	float intervalSec_,
	int sameEmissiveNum_,
	float lifeTime_,
	float lifeTimeLimit_,
	const Vector3& basePos_,
	float initSpeed_,
	float initSize_,
	float initAlpha_,
	const Vector2& billboardOrigin_,
	float addSpeed_,
	float addSize_,
	float addAlpha_,
	int blendMode_
	) 
:
Actor(world),
drawID(drawID_),
intervalSec(intervalSec_),
sameEmissiveNum(sameEmissiveNum_),
lifeTime(lifeTime_),
lifeTimeLimit(lifeTimeLimit_),
basePos(basePos_),
initSpeed(initSpeed_),
initSize(initSize_),
initAlpha(initAlpha_),
billboardOrigin(billboardOrigin_),
addSpeed(addSpeed_),
addSize(addSize_),
addAlpha(addAlpha_),
blendMode(blendMode_)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::PARTICLE_ACTOR;
}
ParticleSystem::~ParticleSystem()
{

}
void ParticleSystem::Update()
{

}
void ParticleSystem::Draw() const
{

}
void ParticleSystem::OnCollide(Actor& other, CollisionParameter colpara)
{

}