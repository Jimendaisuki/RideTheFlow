#include "CastleManager.h"
#include "CastleParameter.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../time/Time.h"
#include "../../game/Random.h"
#include "../castle/MasterCastle.h"
#include <memory>

CastleManager::CastleManager(IWorld& world) :
Actor(world),
rankUpTimer(0.0f),
rankUpNum(0),
count(0)
{
	parameter.isDead = false;
}

CastleManager::~CastleManager()
{

}

void CastleManager::Update()
{

	if (world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR).empty())return;
	int masterCount = world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR).size();
	rankUpTimer += Time::DeltaTime;
	if (RankUpSecond <= rankUpTimer)
	{
		rankUpNum = Random::GetInstance().Range(0, masterCount);
		if (!std::static_pointer_cast<MasterCastle>(world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR)[rankUpNum])->NoRankUp())
		{
			std::static_pointer_cast<MasterCastle>(world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR)[rankUpNum])->RankUp();
			rankUpTimer = 0.0f;
		}
	}
}

void CastleManager::Draw() const
{

}

void CastleManager::OnCollide(Actor& other, CollisionParameter colpara)
{

}