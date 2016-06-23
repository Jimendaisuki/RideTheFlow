#include "BreakCastle.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include <algorithm>
#include "BreakCastleParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"

//流れに流されている時の速度
static const float FlowSpeed = 40.0f;

BreakCastle::BreakCastle(IWorld& world, const Vector3& position_, const Vector3& vec_, const CASTLE_SELECT& castle_, const BREAK_SELECT& break_) :
Actor(world),
moveVec(vec_),
castleSelect(castle_),
breakSelect(break_),
rotX(0.0f),
rotY(0.0f)
{
	parameter.id = ACTOR_ID::PARTICLE_ACTOR;
	parameter.isDead = false;
	parameter.radius = 50.0f;
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
	//当たり判定セット
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CLOUD_WIND_COL);

	//パーティクル更新
	UpdateParticles();

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;

	ps_parameter.position += moveVec * FlowSpeed * Time::DeltaTime;
}
void BreakCastle::Draw() const
{
	DrawParticles();
}
void BreakCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::CLOUD_WIND_COL)
	{
		moveVec = colpara.colVelosity;
	}
}

void BreakCastle::Emissive()
{
	////モデルID、壊れ方、座標、風の流れor竜巻で壊れたときの移動方向*移動量、初期回転X、初期回転Y
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position, vec, rotX, rotY));
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(0, 36, 0), vec, rotX, rotY));
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(0, 10, -26), vec, rotX, rotY));

	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(-26, 16, 10), vec, rotX, rotY + 90));
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(-26, 16, -10), vec, rotX, rotY + 90));
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(26, 16, 10), vec, rotX, rotY - 90));
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(26, 16, -10), vec, rotX, rotY - 90));
	//AddParticle(std::make_shared<BreakCastleParticle>(
	//	MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(0, 16, 26), vec, rotX, rotY + 180));

	//for (int i = 0; i < 4; i++)
	//{
	//	AddParticle(std::make_shared<BreakCastleParticle>(
	//		MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(-42 + 28 * i, 4, 36), vec, rotX, rotY));
	//	AddParticle(std::make_shared<BreakCastleParticle>(
	//		MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position,ps_parameter.position + Vector3(-42 + 28 * i, 4, -36), vec, rotX, rotY));
	//}
}

void BreakCastle::TornadoBreak()
{

}

void BreakCastle::WindFlowBreak()
{

}

void BreakCastle::WindBallBreak()
{

}