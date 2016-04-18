#include "EnemyBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include <math.h>
EnemyBullet::EnemyBullet(IWorld& world):
Actor(world),
playerMat(Matrix4::Identity),
mPosition(0.0f,0.0f,0.0f),
time(0),
InitialVelocity(0.0f),
vertexTime(0)
{

}
EnemyBullet::~EnemyBullet()
{

}
void EnemyBullet::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

	time += Time::DeltaTime / 60.0f;
	InitialVelocity = sqrt(2 * 9.8f*playerMat.GetPosition().y - parameter.mat.GetPosition().y);
	vertexTime = InitialVelocity / 9.8f;
	mPosition += playerMat.GetPosition() - parameter.mat.GetPosition() / vertexTime / 60.0f;
	parameter.mat=Matrix4::Translate(Vector3(mPosition.x, (float)(InitialVelocity*time - 9.8f / 2 * pow(time, 2)), mPosition.z));


	/*parameter.mat = Matrix4::Translate(enemyAttack.AttackVertex(parameter.mat.GetPosition(), playerMat.GetPosition()));*/
}
void EnemyBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}
void EnemyBullet::OnCollide(Actor& other, CollisionParameter colpara)
{

}