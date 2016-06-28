#include "Sand.h"
#include "../Collision.h"
#include <algorithm>
#include "SandParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"

Sand::Sand(IWorld& world, const Vector3& position_, const Vector3& vec_) :
Actor(world),
randMin(-1000,0,-1000),
randMax(1000,0,1000),
emissiveVec(vec_)
{
	parameter.id = ACTOR_ID::SAND_ACTOR;
	parameter.isDead = false;
	parameter.radius = 10.0f;
	ps_parameter.position = position_;
	ps_parameter.intervalSec = 0.1f;
	ps_parameter.lifeTimeLimit = 10000.0f;
	ps_parameter.sameEmissiveNum = 3;
}
Sand::~Sand()
{

}
void Sand::Update()
{
	//パーティクル更新
	UpdateParticles();

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void Sand::Draw() const
{
	DrawParticles();
}
void Sand::OnCollide(Actor& other, CollisionParameter colpara)
{

}

void Sand::Emissive()
{
	AddParticle(std::make_shared<SandParticle>(
		ps_parameter.position + Vector3(Random::GetInstance().Range(randMin.x, randMax.x), 0.0f, Random::GetInstance().Range(randMin.z, randMax.z)),
		emissiveVec));
}