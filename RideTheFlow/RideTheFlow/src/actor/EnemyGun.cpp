#include "EnemyGun.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"

EnemyGun::EnemyGun(IWorld& world) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(parameter.mat.GetPosition())
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	mDirection = Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition());
}
EnemyGun::~EnemyGun()
{

}
void EnemyGun::Update()
{
	mPosition += mDirection;
	parameter.mat = Matrix4::Translate(mPosition);
}

void EnemyGun::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyGun::OnCollide(Actor& other, CollisionParameter colpara)
{

}