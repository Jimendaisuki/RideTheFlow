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
breakSelect(break_),
pTornado(nullptr)
{
	parameter.id = ACTOR_ID::CASTLE_BREAK_ACTOR;
	parameter.isDead = false;
	parameter.radius = 200.0f;
	ps_parameter.position = position_;
	ps_parameter.intervalSec = 10000.0f;
	ps_parameter.lifeTimeLimit = 12.1f;
	ps_parameter.sameEmissiveNum = 1;
	ps_parameter.trigger = true;

	if (breakSelect == BREAK_SELECT::WIND_BALL || breakSelect == BREAK_SELECT::DAMAGE)
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

	//DrawSphere3D(ps_parameter.position.ToVECTOR(), parameter.radius, 5, Vector3::Blue.ToColor(), Vector3::Blue.ToColor(), FALSE);
}
void BreakCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::CLOUD_WIND_COL)
	{
		velocity = colpara.colVelosity * FlowSpeed;
	}
	else if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
	{
		pTornado = static_cast<Tornado*>(const_cast<Actor*>(&other));	
	}
}

void BreakCastle::Emissive()
{
	switch (breakSelect)
	{
	case BREAK_SELECT::TORNADO: TornadoBreakEmissive(); break;
	case BREAK_SELECT::WIND_FLOW: WindFlowBreakEmissive(); break;
	case BREAK_SELECT::WIND_BALL: WindBallBreakEmissive(); break;
	case BREAK_SELECT::DAMAGE: DamageEmissive(); break;
	default: break;
	}
}

void BreakCastle::TornadoBreakUpdate()
{
	//竜巻と衝突したなら
	if (pTornado)
	{
		Vector3 tornadoPos = pTornado->GetParameter().mat.GetPosition();
		ps_parameter.position = Vector3(tornadoPos.x, ps_parameter.position.y, tornadoPos.z);
	}
	else
	{	
		//当たり判定セット
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
		parameter.mat.SetPosition(ps_parameter.position);
	}
}
void BreakCastle::WindFlowBreakUpdate()
{
	//当たり判定セット
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CLOUD_WIND_COL);
	ps_parameter.position += velocity * Time::DeltaTime;
	parameter.mat.SetPosition(ps_parameter.position);
}
void BreakCastle::WindBallBreakUpdate()
{

}

void BreakCastle::TornadoBreakEmissive()
{
	switch (castleSelect)
	{
	case MASTER_CASTLE:MasterCastleEmissive(Vector3::Zero,45.0f * 2.4f); break;
	case CHILD_CASTLE:MasterCastleEmissive(Vector3::Zero, 45.0f * 1.2f); break;
	case SHIP: ShipEmissive([]{return Vector3::Zero; }); break;
	case ARMY_ENEMY: ArmyEnemyEmissive([&]{return Vector3::Zero; }); break;
	case ISLE1: break;
	default: break;
	}
}
void BreakCastle::WindFlowBreakEmissive()
{
	switch (castleSelect)
	{
	case MASTER_CASTLE:CastleWindFlowBreakEmissive(45.0f * 2.4f); break;
	case CHILD_CASTLE:CastleWindFlowBreakEmissive(45.0f * 1.2f); break;
	case SHIP: ShipEmissive([&]{return RandomVelocity(); }); break; break;
	case ISLE1: break;
	case ARMY_ENEMY: ArmyEnemyEmissive([&]{return RandomVelocity(); }); break;
	default: break;
	}
}
void BreakCastle::WindBallBreakEmissive()
{
	switch (castleSelect)
	{
	case MASTER_CASTLE:MasterCastleEmissive(Vector3::Zero, 45.0f * 2.4f); break;
	case CHILD_CASTLE:MasterCastleEmissive(Vector3::Zero, 45.0f * 1.2f); break;
	case SHIP:ShipEmissive([]{return Vector3::Zero; }); break;
	case ISLE1: break;
	case ARMY_ENEMY: ArmyEnemyEmissive([&]{
						 Random &r = Random::GetInstance();
						 return Vector3(r.Range(-1.0f, 1.0f), r.Range(0.0f, 1.0f), r.Range(-1.0f, 1.0f)).Normalized() * r.Range(3.0f, 9.0f)
							 * 20.0f;
	}); break;
	default: break;
	}
}

void BreakCastle::DamageEmissive()
{
	switch (castleSelect)
	{
	case MASTER_CASTLE:CastleDamageEmissive([&]{return RandomVelocity() * 20.0f; }); break;
	case SHIP:ShipDamageEmissive([&]{return RandomVelocity() * 10.0f; }); break;
	default: break;
	}
}


void BreakCastle::CastleWindFlowBreakEmissive(float scale_)
{
	//モデルID、壊れ方、座標、移動方向*移動量、初期回転X、初期回転Y
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, RandomVelocity(), 0, 0, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 36, 0), RandomVelocity(), 0, 0, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 10, -26), RandomVelocity(), 0, 0, scale_));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, 10), RandomVelocity(), 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, -10), RandomVelocity(), 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, 10), RandomVelocity(), 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, -10), RandomVelocity(), 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 16, 26), RandomVelocity(), 0, 180, scale_));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, 36), RandomVelocity(), 0, 0, scale_));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, -36), RandomVelocity(), 0, 0, scale_));
	}
}
void BreakCastle::MasterCastleEmissive(const Vector3& vec_, float scale_)
{
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, vec_, 0, 0, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 36, 0), vec_, 0, 0, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 10, -26), vec_, 0, 0, scale_));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, 10), vec_, 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, -10), vec_, 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, 10), vec_, 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, -10), vec_, 0, 90, scale_));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 16, 26), vec_, 0, 180, scale_));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, 36), Vector3::Zero, 0, 0, scale_));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, -36), Vector3::Zero, 0, 0, scale_));
	}
}


void BreakCastle::ShipEmissive(std::function<Vector3()> vecFunc)
{
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 0, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_2_MODEL, breakSelect, &ps_parameter.position, Vector3(-20, 20, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_3_MODEL, breakSelect, &ps_parameter.position, Vector3(-20, 30, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_4_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 30, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-40, 20, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 40, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_7_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 36, 26), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_7_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 36, -26), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_9_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 20, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_11_MODEL, breakSelect, &ps_parameter.position, Vector3(-40, 40, 0), vecFunc(), 0, 0, 1.0f));
}

void BreakCastle::CastleDamageEmissive(std::function<Vector3()> vecFunc)
{
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_3_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, vecFunc(), 0.0f, 0.0f, 45.0f * 2.4f));
	for (int i = 0; i < 6; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, vecFunc(), 30.0f*i, 30.0f*i, 45.0f * 2.4f));
	}
}

void BreakCastle::ShipDamageEmissive(std::function<Vector3()> vecFunc)
{
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-40, 20, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 40, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_9_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 20, 0), vecFunc(), 0, 0, 1.0f));
	AddParticle(std::make_shared<BreakCastleParticle>(MODEL_ID::SHIP_BREAK_11_MODEL, breakSelect, &ps_parameter.position, Vector3(-40, 40, 0), vecFunc(), 0, 0, 1.0f));
}

void BreakCastle::ArmyEnemyEmissive(std::function<Vector3()> vecFunc)
{
	for (int i = 0; i < 9; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::HUMAN_BALLISTA_MODEL, breakSelect, &ps_parameter.position,	Vector3::Zero, vecFunc(), 30.0f*i, 30.0f*i, 4.0f));
	}
}

Vector3 BreakCastle::RandomVelocity()
{
	Random &r = Random::GetInstance();
	return Vector3(r.Range(-1.0f, 1.0f), r.Range(-1.0f, 1.0f), r.Range(-1.0f, 1.0f)).Normalized() * r.Range(3.0f, 9.0f);
}