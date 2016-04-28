#include "Sand.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../time/Time.h"
#include "../graphic/TextDraw.h"
#include "../math/Math.h"
#include "../game/Random.h"

Sand::Sand(IWorld& world) :
Actor(world)
//,drawPositions(Vector2(Random::GetInstance().Range(-300.0f, -150.0f), Random::GetInstance().Range(-200.0f, -100.0f)))
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::SAND_ACTOR;

	for (int i = 0; i < 20; i++)
	{
		drawPositions[i] = Vector2(
			Random::GetInstance().Range(-400 + i, 200 + i),
			Random::GetInstance().Range(-600 + i, -200 + i));
	}
}
Sand::~Sand()
{

}
void Sand::Update()
{
	for (int i = 0; i<20; i++)
	{
		drawPositions[i] += Vector2::One * 1000.0f * Time::DeltaTime;
		if (drawPositions[i].y > 1200)
			drawPositions[i] = Vector2(
			Random::GetInstance().Range(-400.0f, 200.0f),
			Random::GetInstance().Range(-300.0f, -200.0f));
	}
}
void Sand::Draw() const
{
	for (int i = 0; i < 20; i++)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SAND_SPRITE, drawPositions[i]);
	}
}
void Sand::OnCollide(Actor& other, CollisionParameter colpara)
{

}