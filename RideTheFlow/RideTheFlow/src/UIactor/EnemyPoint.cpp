#include "EnemyPoint.h"

const float Scale = 0.6f;
const Vector2 MAP_POSITION = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) - Vector2(256) * Scale;
const Vector2 StageSize = Vector2(3000, 3000);
const float ReSIZE = 256.0f / StageSize.x * Scale;

EnemyPoint::EnemyPoint(IWorld& world_, Actor& enemy_) :
UIActor(world_),
enemy(&enemy_)
{
	parameter.id = UI_ID::ENEMY_POINT_UI;
	parameter.isDead = false;
	
 	switch (enemy->GetParameter().id)
	{
	case ACTOR_ID::MASTER_CASTLE_ACTOR:
		scale = 0.5f;
		break;
	case ACTOR_ID::SHIP_ENEMY_ACTOR:
		scale = 0.3f;
		break;
	case ACTOR_ID::ARMY_ENEMY_ACTOR:
		scale = 0.2f;
		break;
	default:
		scale = 0;
		parameter.isDead = true;
		break;
	}
}

EnemyPoint::~EnemyPoint()
{

}

void EnemyPoint::Update()
{
	
	if (enemy==nullptr)
	{
		parameter.isDead = true;
		return;
	}

	Vector3 enemyPos = enemy->GetParameter().mat.GetPosition();
	Vector2 pos = Vector2(enemyPos.x, -enemyPos.z);
	if (pos.Length() != 0.0f)
		drawPosition = MAP_POSITION + pos.Normalized() * pos.Length() * ReSIZE;
	else
		drawPosition = MAP_POSITION;
}

void EnemyPoint::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::ENEMY_SPRITE, drawPosition, Vector2(32, 32), 1.0f, scale, 0, true, false);
}