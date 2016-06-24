#include "BreakCastle.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include <algorithm>
#include "BreakCastleParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"

//����ɗ�����Ă��鎞�̑��x
static const float FlowSpeed = 60.0f;

BreakCastle::BreakCastle(IWorld& world, const Vector3& position_, const Vector3& velocity_, const CASTLE_SELECT& castle_, const BREAK_SELECT& break_) :
Actor(world),
velocity(velocity_),
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
	//�p�[�e�B�N���X�V
	UpdateParticles();

	//�V�X�e��������������A�N�^�[��������
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
	ps_parameter.position += velocity * Time::DeltaTime;
	parameter.mat.SetPosition(ps_parameter.position);
}

void BreakCastle::TornadoBreakEmissive()
{
	//���f��ID�A�����A���W�A�ړ�����*�ړ��ʁA������]X�A������]Y
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, Vector3::Zero, rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 36, 0), Vector3::Zero, rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 10, -26), Vector3::Zero, rotX, rotY));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, 10), Vector3::Zero, rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(-26, 16, -10), Vector3::Zero, rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, 10), Vector3::Zero, rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(26, 16, -10), Vector3::Zero, rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, Vector3(0, 16, 26), Vector3::Zero, rotX, rotY + 180));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, 36), Vector3::Zero, rotX, rotY));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, Vector3(-42 + 28 * i, 4, -36), Vector3::Zero, rotX, rotY));
	}
}

void BreakCastle::WindFlowBreakUpdate()
{
	//�����蔻��Z�b�g
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CLOUD_WIND_COL);
	ps_parameter.position += velocity * Time::DeltaTime;
	parameter.mat.SetPosition(ps_parameter.position);
}

void BreakCastle::WindFlowBreakEmissive()
{
	//���f��ID�A�����A���W�A�ړ�����*�ړ��ʁA������]X�A������]Y
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, Vector3::Zero, RandomVelocity(), rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position,  Vector3(0, 36, 0), RandomVelocity(), rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position,  Vector3(0, 10, -26), RandomVelocity(), rotX, rotY));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(-26, 16, 10), RandomVelocity(), rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(-26, 16, -10), RandomVelocity(), rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(26, 16, 10), RandomVelocity(), rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(26, 16, -10), RandomVelocity(), rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position,  Vector3(0, 16, 26), RandomVelocity(), rotX, rotY + 180));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position,  Vector3(-42 + 28 * i, 4, 36), RandomVelocity(), rotX, rotY));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position,  Vector3(-42 + 28 * i, 4, -36), RandomVelocity(), rotX, rotY));
	}
}

void BreakCastle::WindBallBreakUpdate()
{

}

void BreakCastle::WindBallBreakEmissive()
{
	//���f��ID�A�����A���W�A�ړ�����*�ړ��ʁA������]X�A������]Y
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_1_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position, velocity, rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_2_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(0, 36, 0), velocity, rotX, rotY));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_4_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(0, 10, -26), velocity, rotX, rotY));

	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(-26, 16, 10), velocity, rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(-26, 16, -10), velocity, rotX, rotY + 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(26, 16, 10), velocity, rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(26, 16, -10), velocity, rotX, rotY - 90));
	AddParticle(std::make_shared<BreakCastleParticle>(
		MODEL_ID::CASTLE_BREAK_5_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(0, 16, 26), velocity, rotX, rotY + 180));

	for (int i = 0; i < 4; i++)
	{
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(-42 + 28 * i, 4, 36), velocity, rotX, rotY));
		AddParticle(std::make_shared<BreakCastleParticle>(
			MODEL_ID::CASTLE_BREAK_6_MODEL, breakSelect, &ps_parameter.position, ps_parameter.position + Vector3(-42 + 28 * i, 4, -36), velocity, rotX, rotY));
	}
}

Vector3 BreakCastle::RandomVelocity()
{
	Random &r = Random::GetInstance();
	return Vector3(r.Range(-1.0f, 1.0f), r.Range(-1.0f, 1.0f), r.Range(-1.0f, 1.0f)).Normalized() * r.Range(1.0f, 3.0f);
}