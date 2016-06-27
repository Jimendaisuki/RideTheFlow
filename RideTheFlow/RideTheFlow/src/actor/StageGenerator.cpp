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


StageGenerator::StageGenerator(IWorld& world, const std::string& fileName) :
Actor(world)
{
	parameter.id = ACTOR_ID::STAGE_ACTOR;
	parameter.isDead = false;

	currentRow_ = 0;
	csv_.load("res/" + fileName + ".csv");

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
		//world.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(world, position - Vector3(0, 00, 0), false, true, rotation.y));
		break;
	case 2:	// 家
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<HomeActor>(world, 4.8f, position, rotation));
		break;
	case 3: // 島１
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland>(world, position, rotation, 8, false));
		break;
	case 4: // 島２
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland2>(world, position, rotation, 4.8f));
		break;
	case 5: // 島３
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland3>(world, position, rotation, 4.8f));
		break;
	case 6: // 船
		world.Add(ACTOR_ID::SHIP_ENEMY_ACTOR, std::make_shared<ShipEnemy>(world, 2.4f, position, rotation));
		break;
	default:
		break;
	}
}