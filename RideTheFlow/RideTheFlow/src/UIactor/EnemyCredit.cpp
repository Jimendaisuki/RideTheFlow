#include "EnemyCredit.h"
#include "../world/IWorld.h"


EnemyCredit::EnemyCredit(IWorld& world) :
UIActor(world),
castleCount_(0),
shipCount_(0)
{
	parameter.id = UI_ID::CREDIT_UI;
	parameter.isDead = false;
}

EnemyCredit::~EnemyCredit()
{

}

void EnemyCredit::Update()
{
	castleCount_ = world.GetActorCount(ACTOR_ID::MASTER_CASTLE_ACTOR, ACTOR_ID::MASTER_CASTLE_ACTOR);
	shipCount_   = world.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR);
}

void EnemyCredit::Draw() const
{
	for (int i = shipCount_; i > 0; i--)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SHIP_CREDIT_SPRITE, Vector2(WINDOW_WIDTH - 65.0f * i + 60, WINDOW_HEIGHT - 140.0f), Vector2(104.0f, 60.0f), 1.0f, 0.8f, 0, true, false);
	}
	for (int i = castleCount_; i > 0; i--)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::CASTLE_CREDIT_SPRITE, Vector2(WINDOW_WIDTH - 40.0f * i, WINDOW_HEIGHT - 70.0f), Vector2(67.0f, 67.0f), 1.0f, 0.6f, 0, true, false);
	}
}
