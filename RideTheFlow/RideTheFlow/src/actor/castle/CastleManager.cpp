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
spawnArmyTimer(0.0f),
spawnShipTimer(0.0f)
{
	parameter.isDead = false;
}

CastleManager::~CastleManager()
{

}

void CastleManager::Update()
{
	////èÈÇ™ñ≥Ç©Ç¡ÇΩ
	//if (world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR).empty())return;

	if (world.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR) == 0) return;
	//èÈÇÃêî
	int masterCount = world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR).size();

	//èÈÇÃêœÇ›è„Ç™ÇË
	rankUpTimer += Time::DeltaTime;
	if (RankUpSecond <= rankUpTimer)
	{
		int rankUpNum = Random::GetInstance().Range(0, masterCount);
		std::shared_ptr<MasterCastle> mc = std::static_pointer_cast<MasterCastle>
			(world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR)[rankUpNum]);

		if (!mc->NoRankUp())
		{
			mc->RankUp();
			rankUpTimer = 0.0f;
		}
	}
	//åRë‡
	if (world.GetActorCount(ACTOR_ID::ENEMY_ACTOR,ACTOR_ID::ARMY_ENEMY_ACTOR)<SpawnMaxArmyEnemy)
	spawnArmyTimer += Time::DeltaTime;

	if (SpawnArmyEnemyTime <= spawnArmyTimer)
	{
		int spawnNum = Random::GetInstance().Range(0, masterCount);
		std::shared_ptr<MasterCastle> mc = std::static_pointer_cast<MasterCastle>
			(world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR)[spawnNum]);
		if (!mc->SpawnDecision())
		{
			mc->SpawnEnemy();
			spawnArmyTimer = 0.0f;
		}
	}

	//ëD
	if (world.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR)<SpawnMaxShipEnemey)
		spawnShipTimer += Time::DeltaTime;

	if (SpawnShipEnemyTime <= spawnShipTimer)
	{
		int spawnNum = Random::GetInstance().Range(0, masterCount);
		std::shared_ptr<MasterCastle> mc = std::static_pointer_cast<MasterCastle>
			(world.GetActors(ACTOR_ID::MASTER_CASTLE_ACTOR)[spawnNum]);
		if (mc->SpawnDecision())
		{
			mc->SpawnEnemy();
			spawnShipTimer = 0.0f;
		}
	}
}

void CastleManager::Draw() const
{

}

void CastleManager::OnCollide(Actor& other, CollisionParameter colpara)
{

}