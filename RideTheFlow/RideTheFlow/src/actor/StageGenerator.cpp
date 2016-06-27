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
	// ƒAƒNƒ^[”Ô†Žæ“¾
	const int ActorNo = csv_.geti(currentRow_, CSV_ACTOR_ID);
	// ƒ|ƒWƒVƒ‡ƒ“Žæ“¾
	const Vector3 position = Vector3(
		csv_.getf(currentRow_, CSV_POSITION + 0),
		csv_.getf(currentRow_, CSV_POSITION + 1),
		csv_.getf(currentRow_, CSV_POSITION + 2));
	// ‰ñ“]Šp“x‚ðŽæ“¾
	const Vector3 rotation = Vector3(
		csv_.getf(currentRow_, CSV_ROTATION + 0),
		csv_.getf(currentRow_, CSV_ROTATION + 1) + 180.0f,
		csv_.getf(currentRow_, CSV_ROTATION + 2));

	switch (ActorNo)
	{
	case 1:	// é
		world.Add(ACTOR_ID::MASTER_CASTLE_ACTOR, std::make_shared<MasterCastle>(world, position, 0.0f, 2.4f, false, true, 5));
		break;
	case 2:	// ‰Æ
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<HomeActor>(world, 4.8f, position, rotation));
		break;
	case 3: // “‡‚P
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland>(world, position, rotation, 8, false));
		break;
	case 4: // “‡‚Q
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland2>(world, position, rotation, 4.8f));
		break;
	case 5: // “‡‚R
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Froatinglsland3>(world, position, rotation, 4.8f));
		break;
	case 6: // ‘D
		world.Add(ACTOR_ID::SHIP_ENEMY_ACTOR, std::make_shared<ShipEnemy>(world, 2.4f, position, rotation));
		break;
	default:
		break;
	}
}