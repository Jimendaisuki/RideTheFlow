#include "CastleAdd.h"
#include "../Collision.h"
#include <algorithm>
#include "CastleAddParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"

CastleAdd::CastleAdd(IWorld& world, const Vector3& position_) :
Actor(world)
{
	parameter.id = ACTOR_ID::PARTICLE_ACTOR;
	parameter.isDead = false;
	parameter.radius = 0.0f;
	ps_parameter.position = position_;
	ps_parameter.intervalSec = 10000.0f;
	ps_parameter.lifeTimeLimit = 6.0f;
	ps_parameter.sameEmissiveNum = 30;
}
CastleAdd::~CastleAdd()
{

}
void CastleAdd::Update()
{
	//パーティクル更新
	UpdateParticles();

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void CastleAdd::Draw() const
{
	DrawParticles();
}
void CastleAdd::OnCollide(Actor& other, CollisionParameter colpara)
{

}

void CastleAdd::Emissive()
{
	AddParticle(std::make_shared<CastleAddParticle>(
		ps_parameter.position +
		Vector3(
		Random::GetInstance().Range(-1.0f, 1.0f),
		Random::GetInstance().Range(-0.1f, 0.1f),
		Random::GetInstance().Range(-1.0f, 1.0f)) * 50.0f));
}