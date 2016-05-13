#include "ParticleSystem.h"

#include "Particle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../graphic/TextDraw.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../math/Quaternion.h"

#include<algorithm>

//球or半球
ParticleSystem::ParticleSystem(
	IWorld& world,
	const MODEL_ID& drawID_,
	float intervalSec_,
	int sameEmissiveNum_,
	float lifeTimeLimit_,
	const Vector3& basePos_,
	bool isHalfShpere,
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
lifeTime(0.0f),
lifeTimeLimit(lifeTimeLimit_),
particleLifeTimeLimit(2.0f),
basePos(basePos_),
billboardOrigin(billboardOrigin_),
initSpeed(initSpeed_),
initSize(initSize_),
initAlpha(initAlpha_),
addSpeed(addSpeed_),
addSize(addSize_),
addAlpha(addAlpha_),
blendMode(blendMode_),
emissiveTimer(0.0f)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::PARTICLE_ACTOR;

	if (isHalfShpere)
		shape = PARTICLE_SHAPE::HALF_SPHERE;
	else
		shape = PARTICLE_SHAPE::SPHERE;
}

//箱
ParticleSystem::ParticleSystem(
	IWorld& world,
	const MODEL_ID& drawID_,
	float intervalSec_,
	int sameEmissiveNum_,
	float lifeTimeLimit_,
	float particleLifeTimeLimit_,
	const Vector3& basePos_,
	const Vector3& emissiveVec_,
	const Vector3& boxSize_,
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
lifeTime(0.0f),
lifeTimeLimit(lifeTimeLimit_),
particleLifeTimeLimit(particleLifeTimeLimit_),
basePos(basePos_),
emissiveVec(Vector3::Normalize(emissiveVec_)),
boxSize(boxSize_),
initSpeed(initSpeed_),
initSize(initSize_),
initAlpha(initAlpha_),
billboardOrigin(billboardOrigin_),
addSpeed(addSpeed_),
addSize(addSize_),
addAlpha(addAlpha_),
blendMode(blendMode_),
emissiveTimer(0.0f)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::PARTICLE_ACTOR;
	parameter.mat.SetPosition(basePos);
	shape = PARTICLE_SHAPE::BOX;
}

ParticleSystem::~ParticleSystem()
{

}

Vector3 front;
Vector3 left;
Vector3 up;

void ParticleSystem::Update()
{
	//システムの寿命計算
	lifeTime += Time::DeltaTime;
	if (lifeTime >= lifeTimeLimit)
		parameter.isDead = true;

	//寿命が尽きたパーティクルを削除
	Remove();

	//パーティクルを更新
	std::for_each(particles.begin(), particles.end(),
		[](ParticlePtr par){par->Update();
	});

	//放出
	emissiveTimer += Time::DeltaTime;
	if (emissiveTimer > intervalSec)
	{
		emissiveTimer = 0.0f;
		//球状の放出
		if (shape == PARTICLE_SHAPE::SPHERE)
		{
			for (int i = 0; i < sameEmissiveNum; i++)
			{
				Vector3 v = Vector3(
					Random::GetInstance().Range(-1.0f, 1.0f),
					Random::GetInstance().Range(-1.0f, 1.0f),
					Random::GetInstance().Range(-1.0f, 1.0f)).Normalized();
				Add(std::make_shared<Particle>(
					drawID, particleLifeTimeLimit, basePos, v,
					initSpeed, addSpeed, initSize, addSize, initAlpha, addAlpha, 
					blendMode, billboardOrigin));
			}
		}
		if (shape == PARTICLE_SHAPE::BOX)
		{
			front = emissiveVec;
			Matrix4 pitchmat = Quaternion::RotateAxis(Vector3::Up, 90.0f);
			left = Vector3::Normalize(front * pitchmat);
			up = Vector3::Cross(left, front);

			for (int i = 0; i < sameEmissiveNum; i++)
			{
				Vector3 pos =
					basePos
					+ (left * Random::GetInstance().Range(-boxSize.x / 2.0f, boxSize.x / 2.0f))
					+ (up * Random::GetInstance().Range(-boxSize.y / 2.0f, boxSize.y / 2.0f))
					+ (front * Random::GetInstance().Range(-boxSize.z / 2.0f, boxSize.z / 2.0f));
				Add(std::make_shared<Particle>(
					drawID, particleLifeTimeLimit, pos, emissiveVec,
					initSpeed, addSpeed, initSize, addSize, initAlpha, addAlpha,
					blendMode, billboardOrigin));
			}
		}
	}
}
void ParticleSystem::Draw() const
{
	std::for_each(particles.begin(), particles.end(),
		[](ParticlePtr par){par->Draw(); });

	DrawLine3D(basePos, basePos + front * 100, GetColor(0, 0, 255));
	DrawLine3D(basePos, basePos + up * 100, GetColor(0, 255, 0));
	DrawLine3D(basePos, basePos + left * 100, GetColor(255, 0, 0));
}

void ParticleSystem::OnCollide(Actor& other, CollisionParameter colpara)
{

}

void ParticleSystem::Add(ParticlePtr particle)
{
	particles.push_back(particle);
}

void ParticleSystem::Remove()
{
	particles.remove_if([](ParticlePtr par){return par->GetIsDead(); });
}