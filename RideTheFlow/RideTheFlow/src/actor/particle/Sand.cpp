#include "Sand.h"
#include "../Collision.h"
#include <algorithm>
#include "SandParticle.h"
#include "../../game/Random.h"
#include "WindSetting.h"
#include "../../time/Time.h"

Sand::Sand(IWorld& world,const Vector3& position_) :
Actor(world)
{
	parameter.id = ACTOR_ID::SAND_ACTOR;
	parameter.isDead = false;
	parameter.radius = 10.0f;
	ps_parameter.position = position_;
	ps_parameter.intervalSec = 1.0f;
	ps_parameter.lifeTimeLimit = 120.0f;
	ps_parameter.sameEmissiveNum = 3;
}
Sand::~Sand()
{

}
void Sand::Update()
{
	//�p�[�e�B�N���X�V
	UpdateParticles();

	//�V�X�e��������������A�N�^�[��������
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
	AddParticle(std::make_shared<SandParticle>(ps_parameter.position, Vector3(Random::GetInstance().Range(-1.0f, 1.0f), 1.0f, Random::GetInstance().Range(-1.0f, 1.0f))));
}