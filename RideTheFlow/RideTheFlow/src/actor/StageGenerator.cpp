#include "StageGenerator.h"
#include "Collision.h"
#include "../math/Math.h"
#include "../world/IWorld.h"
#include "castle/MasterCastle.h"
#include "castle\HomeActor.h"
#include "island/Froatinglsland.h"
#include "island/Froatinglsland2.h"
#include "island/Froatinglsland3.h"
#include "enemy/ShipEnemy.h"


StageGenerator::StageGenerator(IWorld& world, const std::string& fileName, bool isGameScene, bool isEndingScene) :
Actor(world),
isGameScene_(isGameScene),
isEndingScene_(isEndingScene)
{
	parameter.id = ACTOR_ID::STAGE_ACTOR;
	parameter.isDead = false;

	currentRow_ = 0;
	csv_.load("res/" + fileName + ".csv");
	tempCount = 0;
	DataLoad();
	parameter.isDead = true;
}

StageGenerator::~StageGenerator()
{

}

void StageGenerator::Update(){}

void StageGenerator::Draw() const{}

void StageGenerator::OnCollide(Actor& other, CollisionParameter coplara){}


void StageGenerator::DataLoad()
{
	while (currentRow_ < csv_.rows())
	{
		AddActor();
		currentRow_++;
	}
}

const int CSV_ACTOR_ID = 0;
const int CSV_POSITION = 1;
const int CSV_ROTATION = 4;
void StageGenerator::AddActor()
{
	// アクター番号取得
	const int ActorNo = csv_.geti(currentRow_, CSV_ACTOR_ID);
	// ポジション取得
	const Vector3 position = Vector3(
		csv_.getf(currentRow_, CSV_POSITION + 0),
		csv_.getf(currentRow_, CSV_POSITION + 1),
		csv_.getf(currentRow_, CSV_POSITION + 2));
	// 回転角度を取得
	const Vector3 rotation = Vector3(
		csv_.getf(currentRow_, CSV_ROTATION + 0),
		csv_.getf(currentRow_, CSV_ROTATION + 1) + 180.0f,
		csv_.getf(currentRow_, CSV_ROTATION + 2));

	switch (ActorNo)
	{
	case 1:	// 城
		if (isEndingScene_)
			break;
		if (isGameScene_)
		{
			if (position.y>0)
				world.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(world, position, rotation.y, 2.4f, true, false, 1));
			else
				world.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(world, position, rotation.y, 2.4f, false, false, 1));
		}
		else
			world.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(world, position, rotation.y, 2.4f, false, true, 5));
		break;
	case 2:	// 家
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<HomeActor>(world, 4.8f, position, rotation));
		break;
	case 3: // 島１
		if (isGameScene_)
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland>(world, position, rotation, 8, true));
		else
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland>(world, position, rotation, 8, false));
		break;
	case 4: // 島２
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland2>(world, position, rotation, 4.8f,isGameScene_));
		break;
	case 5: // 島３
		if (tempCount == 0)
			world.Add(ACTOR_ID::ISLAND_ACTOR, std::make_shared<Froatinglsland3>(world, position, rotation, 8.0f));
		else
			world.Add(ACTOR_ID::ISLAND_ACTOR, std::make_shared<Froatinglsland3>(world, position, rotation, 4.8f));

		tempCount++;
		break;
	case 6: // 船
		if (isEndingScene_)
			break;
		if (!isGameScene_)
		world.Add(ACTOR_ID::SHIP_ENEMY_ACTOR, std::make_shared<ShipEnemy>(world, 2.4f, position, rotation));
		break;
	default:
		break;
	}
}