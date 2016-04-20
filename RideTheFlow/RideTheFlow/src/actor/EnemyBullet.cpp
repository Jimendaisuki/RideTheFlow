#include "EnemyBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include <math.h>
EnemyBullet::EnemyBullet(IWorld& world, float initialVelocity) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(parameter.mat.GetPosition()),
time(0),
mInitialVelocity(initialVelocity),
vertexTime(0)
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	parameter.isDead = false;
}
EnemyBullet::~EnemyBullet()
{

}
void EnemyBullet::Update()
{
	time += Time::DeltaTime;
	


	/*mPosition.y = mInitialVelocity*sin(atan2())*/
}

void EnemyBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyBullet::OnCollide(Actor& other, CollisionParameter colpara)
{

}