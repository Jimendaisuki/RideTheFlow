#include "TornadoParticleSystem.h"
#include "../Collision.h"
#include <algorithm>
#include "TornadoParticle.h"
#include "../../game/Random.h"

//生成する流れの高さ最低値　流れの高さ〜最低値までが縦の長さ
static const float HeightMin = -100.0f;

TornadoParticleSystem::TornadoParticleSystem(IWorld& world, Player& player_) :
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
TornadoParticleSystem::~TornadoParticleSystem()
{

}
void TornadoParticleSystem::Update()
{
	//ダッシュ終了までは座標配列を更新
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
	//ダッシュ終了後は座標配列を更新しない
	else if (size == 0)
	{
		isSetting = true;
	}

	//パーティクル更新
	UpdateParticles();

	//システム寿命が来たらアクターも寿命に
	if (ps_parameter.isDead)
		parameter.isDead = true;
}
void TornadoParticleSystem::Draw() const
{
	DrawParticles();
}
void TornadoParticleSystem::OnCollide(Actor& other, CollisionParameter colpara)
{

}

std::vector<Vector3>& TornadoParticleSystem::GetDashPositions()
{
	return dashPositions;
}

void TornadoParticleSystem::Emissive()
{
	//if (dashPositions.size() > 0)
		//AddParticle(std::make_shared<TornadoParticle>(dashPositions, Random::GetInstance().Range(HeightMin, dashPositions.at(0).y)));
}