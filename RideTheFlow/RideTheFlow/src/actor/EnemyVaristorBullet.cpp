#include "EnemyVaristorBullet.h"

#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"
EnemyVaristorBullet::EnemyVaristorBullet(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position),
time(0),
InitialVelocity(0.0f),
vertexTime(0),
speed(3.0f)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
}
EnemyVaristorBullet::~EnemyVaristorBullet()
{

}
void EnemyVaristorBullet::Update()
{
	time += Time::DeltaTime*speed;

	InitialVelocity = sqrt(2 * 9.8f*playerMat.GetPosition().y - mPosition.y);
	vertexTime = InitialVelocity / 9.8f;
	mPosition.x += (playerMat.GetPosition().x - mPosition.x) / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
	mPosition.z += (playerMat.GetPosition().z - mPosition.z) / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
	mPosition = Vector3(mPosition.x, (float)(InitialVelocity*time - 9.8f / 2 * pow(time, 2)), mPosition.z);
	parameter.mat = Matrix4::Translate(mPosition);
}

void EnemyVaristorBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyVaristorBullet::OnCollide(Actor& other, CollisionParameter colpara)
{

}