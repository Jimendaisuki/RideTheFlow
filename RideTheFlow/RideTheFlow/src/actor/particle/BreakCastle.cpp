#include "BreakCastle.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include <algorithm>
#include "BreakCastleParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"


//流れに流されている時の速度
static const float FlowSpeed = 160.0f;

BreakCastle::BreakCastle(IWorld& world, const Vector3& position_, const CASTLE_SELECT& castle_, const BREAK_SELECT& break_) :
Actor(world),
velocity(Vector3::Zero),
castleSelect(castle_),
breakSelect(break_)
{
	parameter.id = ACTOR_ID::CASTLE_BREAK_ACTOR;
	parameter.isDead = false;
	parameter.radius = 200.0f;
	ps_parameter.position = position_;
	ps_parameter.intervalSec = 10000.0f;
	ps_parameter.lifeTimeLimit = 12.1f;
	ps_parameter.sameEmissiveNum = 1;
	ps_parameter.trigger = true;

	if (breakSelect == BREAK_SELECT::WIND_BALL)
		ps_parameter.lifeTimeLimit = 3.1f;
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

	switch (breakSelect)
	{
	case TORNADO: TornadoBreakUpdate(); break;
	case WIND_FLOW: WindFlowBreakUpdate(); break;
	case WIND_BALL: WindBallBreakUpdate(); break;
	default:
		break;
	}

}
void BreakCastle::Draw() const
{
	DrawParticles();

	DrawSphere3D(ps_parameter.position.ToVECTOR(), parameter.radius, 5, Vector3::Blue.ToColor(), Vector3::Blue.ToColor(), FALSE);
}
void BreakCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::CLOUD_WIND_COL)
	{
		velocity = colpara.colVelosity * FlowSpeed;
	}
	else if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
	{
		ps_parameter.position = Vector3(colpara.colPos.x, ps_parameter.position.y, colpara.colPos.z);
	}
}

void BreakCastle::Emissive()
{
	switch (breakSelect)
	{
	case TORNADO: TornadoBreakEmissive(); break;
	case WIND_FLOW: WindFlowBreakEmissive(); break;
	case WIND_BALL: WindBallBreakEmissive(); break;
	default:
		break;
	}
}

void BreakCastle::TornadoBreakUpdate()
{
	//当たり判定セット
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	parameter.mat.SetPosition(ps_parameter.position);
}

void BreakCastle::TornadoBreakEmissive()
{
	CastleEmissive(Vector3::Zero);
}

void BreakCastle::WindFlowBreakUpdate()
{
	//当たり判定セット
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CLOUD_WIND_COL);
	ps_parameter.position += velocity * Time::DeltaTime;
	parameter.mat.SetPosition(ps_parameter.position);
}

void BreakCastle::WindFlowBreakEmissive()
{
	//モデルID、壊れ方、座標、移動方向*移動量、初期回転X、初期回転Y
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, RandomVelocity(), 0, 0));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position,  Vector3(0, 36, 0), RandomVelocity(), 0, 0));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position,  Vector3(0, 10, -26), RandomVelocity(), 0, 0));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(-26, 16, 10), RandomVelocity(), 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(-26, 16, -10), RandomVelocity(), 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(26, 16, 10), RandomVelocity(), 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(26, 16, -10), RandomVelocity(), 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(0, 16, 26), RandomVelocity(), 0, 180));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position,  Vector3(-42 + 28 * i, 4, 36), RandomVelocity(), 0, 0));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position,  Vector3(-42 + 28 * i, 4, -36), RandomVelocity(), 0, 0));
	}
}

void BreakCastle::WindBallBreakUpdate()
{

}

void BreakCastle::WindBallBreakEmissive()
{
	CastleEmissive(Vector3::Zero);
}

void BreakCastle::CastleEmissive(const Vector3& vec_)
{
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, vec_, 0, 0));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 36, 0), vec_, 0, 0));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 10, -26), vec_, 0, 0));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, 10), vec_, 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, -10), vec_, 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, 10), vec_, 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, -10), vec_, 0, 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 16, 26), vec_, 0, 180));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, 36), Vector3::Zero, 0, 0));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, -36), Vector3::Zero, 0, 0));
	}
}

Vector3 BreakCastle::RandomVelocity()
{
	Random &r = Random::GetInstance();
	return Vector3(r.Range(-1.0f, 1.0f), r.Range(-1.0f, 1.0f), r.Range(-1.0f, 1.0f)).Normalized() * r.Range(3.0f, 9.0f);
}