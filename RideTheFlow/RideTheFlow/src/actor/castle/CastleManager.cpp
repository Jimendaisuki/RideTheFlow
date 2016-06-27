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
rankUpNum(0)
{
	parameter.isDead = false;
}

CastleManager::~CastleManager()
{

}

void CastleManager::Update()
{
	int masterCount = world.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR);
	rankUpTimer += Time::DeltaTime;
	
	if (RankUpSecond <= rankUpTimer)
	{
		rankUpNum = Random::GetInstance().Range(0, masterCount);
		std::static_pointer_cast<MasterCastle>(world.GetMasterCastle()[rankUpNum])->RankUp();
		rankUpTimer = 0.0f;
	}
}

void CastleManager::Draw() const
{

}

void CastleManager::OnCollide(Actor& other, CollisionParameter colpara)
{

}