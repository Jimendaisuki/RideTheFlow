#include "BreakCastle.h"
#include "../Collision.h"
#include <algorithm>
#include "BreakCastleParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"

BreakCastle::BreakCastle(IWorld& world, const Vector3& position_, const CASTLE_SELECT& select) :
Actor(world),
rotX(0.0f),
rotY(0.0f)
{
	parameter.id = ACTOR_ID::PARTICLE_ACTOR;
	parameter.isDead = false;
	parameter.radius = 0.0f;
	ps_parameter.position = position_;
	ps_parameter.intervalSec = 10000.0f;
	ps_parameter.lifeTimeLimit = 20.0f;
	ps_parameter.sameEmissiveNum = 1;
	ps_parameter.trigger = true;
}
BreakCastle::~BreakCastle()
{

}
void BreakCastle::Update()
{
	//パーティクル更新
	UpdateParticles();

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void BreakCastle::Draw() const
{
	DrawParticles();
}
void BreakCastle::OnCollide(Actor& other, CollisionParameter colpara)
{

}

void BreakCastle::Emissive()
{
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, ps_parameter.position, rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, ps_parameter.position + Vector3(0, 36, 0), rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, ps_parameter.position + Vector3(0, 10, -26), rotX, rotY));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, ps_parameter.position + Vector3(-26, 16, 10), rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, ps_parameter.position + Vector3(-26, 16, -10), rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, ps_parameter.position + Vector3(26, 16, 10), rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, ps_parameter.position + Vector3(26, 16, -10), rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, ps_parameter.position + Vector3(0, 16, 26), rotX, rotY + 180));

	//for (int i = 0; i < 5; i++)
	//{
	//	AddParticle(std::make_shared<BreakCastleParticle>(
	//		MODEL_ID::CASTLE_BREAK_6_MODEL, ps_parameter.position + Vector3(60, 0, 60), rotX, rotY));
	//}
}