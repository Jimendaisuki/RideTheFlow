#include "StageGenerator.h"
#include "Collision.h"
#include "castle\MasterCastle.h"
#include "../world/IWorld.h"

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
		csv_.getf(currentRow_, CSV_POSITION + 2))
		* Vector3(2.3f, 1.5f, 2.3f) + Vector3(0.0f, 250.0f, 0.0f);
	// 回転角度を取得
	const Vector3 rotation = Vector3(
		csv_.getf(currentRow_, CSV_ROTATION + 0),
		csv_.getf(currentRow_, CSV_ROTATION + 1),
		csv_.getf(currentRow_, CSV_ROTATION + 2));

	switch (ActorNo)
	{
	case 1:	// 城
		world.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(world, position - Vector3(0, 70, 0), false, true, rotation.y));

		break;
	case 2:	// 
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	default:
		break;
	}
}