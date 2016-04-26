#include "EnemyVaristorBullet.h"

#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"
EnemyVaristorBullet::EnemyVaristorBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position),
time(0),
InitialVelocity(0.0f),
vertexTime(0),
speed(3.0f),
distance(0, 0, 0)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	parameter.radius = 5.0f;
	distance = playerMat.GetPosition() - mPosition;
}
EnemyVaristorBullet::~EnemyVaristorBullet()
{

}
void EnemyVaristorBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	time += Time::DeltaTime*speed;

	InitialVelocity = sqrt(2 * 9.8f*playerMat.GetPosition().y - mPosition.y);
	vertexTime = InitialVelocity / 9.8f;
	mPosition.x += distance.x / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
	mPosition.z += distance.z / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
	mPosition = Vector3(mPosition.x, (InitialVelocity*time - 9.8f / 2.0f * pow(time, 2)) + 5.0f, mPosition.z);
	parameter.mat = Matrix4::Translate(mPosition);
}

void EnemyVaristorBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyVaristorBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}