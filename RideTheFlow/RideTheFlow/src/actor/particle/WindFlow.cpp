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
	parameter.isDead = false;
	ps_parameter.intervalSec = 0.01f;
	ps_parameter.lifeTimeLimit = 15.0f;
	ps_parameter.sameEmissiveNum = 1;
}
WindFlow::~WindFlow()
{

}
void WindFlow::Update()
{
	//�_�b�V���I���܂ł͍��W�z����X�V
	int size = player.ReturnDashPosStorage().size();
	if (size > 0)
	{
		if (!isSetting)
			dashPositions = player.ReturnDashPosStorage();
	}
	//�_�b�V���I����͍��W�z����X�V���Ȃ�
	else
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


void WindFlow::Emissive()
{
	if (dashPositions.size() > 0)
		AddParticle(std::make_shared<WindFlowParticle>(dashPositions, Random::GetInstance().Range(HeightMin, dashPositions.at(0).y)));
}