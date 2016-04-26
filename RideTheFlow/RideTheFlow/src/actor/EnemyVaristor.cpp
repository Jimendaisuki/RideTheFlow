#include "EnemyVaristor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"
#include "EnemyVaristorBullet.h"
EnemyVaristor::EnemyVaristor(IWorld& world, Vector3 position) :
Actor(world),
coolTime(10.0f),
time(0.0f),
attack(true),
mPosition(position)
{
	parameter.isDead = false;
	
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	
}
EnemyVaristor::~EnemyVaristor()
{

}
void EnemyVaristor::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	if (Vector3::Distance(playerMat.GetPosition(), mPosition) <= 40.0f&&attack)
	{
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyVaristorBullet>(world, mPosition));
		time = 0;
		attack = false;
	}
	else
	{
		time += Time::DeltaTime;
		if (time >= coolTime)
			attack = true;
	}
}

void EnemyVaristor::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, mPosition);
}

void EnemyVaristor::OnCollide(Actor& other, CollisionParameter colpara)
{

}