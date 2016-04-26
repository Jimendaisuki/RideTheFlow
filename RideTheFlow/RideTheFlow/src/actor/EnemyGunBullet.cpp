#include "EnemyGunBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"

EnemyGunBullet::EnemyGunBullet(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	mDirection = Vector3::Direction(mPosition, playerMat.GetPosition()).Normalized();
}
EnemyGunBullet::~EnemyGunBullet()
{

}
void EnemyGunBullet::Update()
{
	mPosition += mDirection*Time::DeltaTime*60.0f;
	parameter.mat = Matrix4::Translate(mPosition);
}

void EnemyGunBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyGunBullet::OnCollide(Actor& other, CollisionParameter colpara)
{

}