#include "EnemyPoint.h"
#include "MiniMapParameter.h"

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
	enemy = nullptr;
}

void EnemyPoint::Update()
{
	
	if (enemy == nullptr || enemy->GetParameter().isDead)
	{
		parameter.isDead = true;
		return;
	}

	Vector3 enemyPos = enemy->GetParameter().mat.GetPosition();
	Vector2 pos = Vector2(enemyPos.x, -enemyPos.z);
	if (pos.Length() != 0.0f)
		drawPosition = MAP_DRAW_POSITION + pos.Normalized() * pos.Length() * RE_SIZE_SCALE;
	else
		drawPosition = MAP_DRAW_POSITION;
}

void EnemyPoint::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::ENEMY_SPRITE, drawPosition, Vector2(32, 32), 1.0f, scale, 0, true, false);
}