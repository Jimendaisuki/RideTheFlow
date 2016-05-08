#include "ParticleSystem.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../time/Time.h"
#include "../graphic/TextDraw.h"
#include "../math/Math.h"
#include "../game/Random.h"

//要素削除用関数
template<typename T>
void remove(std::vector<T>& vector, int index)
{
	vector.erase(vector.begin() + index);
}

ParticleSystem::Particle::Particle(
	const Vector3& pos_,
	const Vector3& vec_,
	float life_,
	float speed_,
	float size_,
	float alpha_,
	float addSpeed_,
	float addSize_,
	float addAlpha_)
{
	pos = pos_;
	vec = vec_;
	lifeTime = 0.0f;
	lifeTimeLimit = life_;
	isDead = false;
	speed = speed_;
	addSpeed = addSpeed_;
	size = size_;
	addSize = addSize_;
	alpha = alpha_;
	addAlpha = addAlpha_;
}

void ParticleSystem::Particle::Initialize(
	const Vector3& pos_,
	const Vector3& vec_,
	float speed_,
	float size_,
	float alpha_,
	float addSpeed_, 
	float addSize_,
	float addAlpha_)
{
	pos = pos_;
	vec = vec_;
	speed = speed_;
	addSpeed = addSpeed_;
	size = size_;
	addSize = addSize_;
	alpha = alpha_;
	addAlpha = addAlpha_;
}

void ParticleSystem::Particle::Update()
{
	lifeTime += Time::DeltaTime;
	if (lifeTime > lifeTimeLimit)
		isDead = true;
	else
	{
		pos += vec * speed *  Time::DeltaTime;
		speed += addSpeed * Time::DeltaTime;
		size += addSize * Time::DeltaTime;
		alpha += addAlpha * Time::DeltaTime;
	}
}

void ParticleSystem::Particle::Draw(const MODEL_ID& drawID, Vector2 origin, const int& blend_mode) const
{
	if (blend_mode == BLEND_MODE::NoBlend)
		Model::GetInstance().Draw2D(drawID, pos, 0, size, origin, 0);
	else
		Model::GetInstance().Draw2DBlend(drawID, pos, 0, size, origin, 0, blend_mode, alpha);
}

bool ParticleSystem::Particle::GetIsDead()
{
	return isDead;
}

ParticleSystem::ParticleSystem(
	IWorld& world,
	const MODEL_ID& drawID_,
	float intervalSec_,
	int sameEmissiveNum_,
	float lifeTimeLimit_,
	const Vector3& basePos_,
	bool isShpere,
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
basePos(basePos_),
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

	if (isShpere)
		shape = PARTICLE_SHAPE::SPHERE;
	else
		shape = PARTICLE_SHAPE::HALF_SPHERE;
}
ParticleSystem::~ParticleSystem()
{

}
void ParticleSystem::Update()
{
	//寿命計算
	lifeTime += Time::DeltaTime;
	if (lifeTime >= lifeTimeLimit)
		parameter.isDead = true;

	//寿命が尽きたパーティクルを削除
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i].GetIsDead())
			remove(particles, i);
	}

	//パーティクルを更新
	for (Particle p : particles)
	{
		p.Update();
	}

	//放出
	emissiveTimer += Time::DeltaTime;
	if (emissiveTimer > intervalSec)
	{
		//球状の放出
		if (shape == PARTICLE_SHAPE::SPHERE)
		{
			for (int i = 0; i < sameEmissiveNum; i++)
			{
				Vector3 v = Vector3(
					Random::GetInstance().Range(-1.0f, 1.0f),
					Random::GetInstance().Range(-1.0f, 1.0f),
					Random::GetInstance().Range(-1.0f, 1.0f)).Normalized();
				Particle par = Particle(basePos, v, initSpeed, initSize, initAlpha, addSpeed, addSize, addAlpha);
				particles.push_back(par);
			}
		}
	}
}
void ParticleSystem::Draw() const
{
	for (Particle p : particles)
	{
		p.Draw(drawID, billboardOrigin, blendMode);
	}
}
void ParticleSystem::OnCollide(Actor& other, CollisionParameter colpara)
{

}