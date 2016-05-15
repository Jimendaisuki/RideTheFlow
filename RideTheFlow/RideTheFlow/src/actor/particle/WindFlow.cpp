#include "WindFlow.h"
#include "../Collision.h"
#include <algorithm>
#include "WindFlowParticle.h"
#include "../../game/Random.h"

//�������闬��̍����Œ�l�@����̍����`�Œ�l�܂ł��c�̒���
static const float HeightMin = -100.0f;

WindFlow::WindFlow(IWorld& world, Player& player_) :
Actor(world),
player(player_),
isSetting(false)
{
	parameter.id = ACTOR_ID::WIND_ACTOR;
	parameter.isDead = false;
	parameter.height = Vector3::Up * HeightMin;
	parameter.radius = 5.0f;
	ps_parameter.intervalSec = 0.01f;
	ps_parameter.lifeTimeLimit = 15.0f;
	ps_parameter.sameEmissiveNum = 1;
	dashPositions = player.ReturnDashPosStorage();
}
WindFlow::~WindFlow()
{

}
void WindFlow::Update()
{
	//�_�b�V���I���܂ł͍��W�z����X�V
	int size = player.ReturnDashPosStorage().size();
	if (size > 0 && !isSetting)
	{
		dashPositions.clear();
		for (int i = 0; i < size; i++)
		{
			if (i % 5 == 0)
				dashPositions.push_back(player.ReturnDashPosStorage().at(i));
		}
	}
	//�_�b�V���I����͍��W�z����X�V���Ȃ�
	else if (size == 0)
	{
		isSetting = true;
	}

	//�p�[�e�B�N���X�V
	UpdateParticles();

	//�V�X�e��������������A�N�^�[��������
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void WindFlow::Draw() const
{
	DrawParticles();
}
void WindFlow::OnCollide(Actor& other, CollisionParameter colpara)
{

}

std::vector<Vector3>& WindFlow::GetDashPositions()
{
	return dashPositions;
}

void WindFlow::Emissive()
{
	if (dashPositions.size() > 0)
		AddParticle(std::make_shared<WindFlowParticle>(dashPositions, Random::GetInstance().Range(HeightMin, dashPositions.at(0).y)));
}