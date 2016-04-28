#include "EnemyVaristorBullet.h"

#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"
EnemyVaristorBullet::EnemyVaristorBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale,Vector3 randomTarget) :
Actor(world),
playerMat(Matrix4::Identity),
time(0),
InitialVelocity(0.0f),
vertexTime(0),
speed(3.0f),
distance(0, 0, 0),
mPosition(position),
coppyPosition(position),
mRandomTarget(randomTarget)
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	parameter.isDead = false;
	parameter.radius = 10.0f;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	distance = (playerMat.GetPosition() + mRandomTarget)- mPosition;
}
EnemyVaristorBullet::~EnemyVaristorBullet()
{

}
void EnemyVaristorBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	time += Time::DeltaTime*speed;
	if (coppyPosition.y < playerMat.GetPosition().y)
	{
		InitialVelocity = sqrt(2 * 9.8f*(playerMat.GetPosition().y - coppyPosition.y) - mPosition.y);
		vertexTime = InitialVelocity / 9.8f;
		mPosition.x += distance.x / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
		mPosition.z += distance.z / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
		mPosition.y = (InitialVelocity*time - 9.8f / 2.0f * pow(time, 2));
	}
	else
	{
		vertexTime = sqrt((2 * (coppyPosition.y - playerMat.GetPosition().y)) / 9.8f);
		mPosition.y = -(1.0f / 2.0f) * 9.8f*pow(time, 2);
		mPosition.x += distance.x / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
		mPosition.z += distance.z / vertexTime / 60.0f*speed*Time::DeltaTime*60.0f;
	}
	parameter.mat = Matrix4::Translate(mPosition+Vector3(0.0f,coppyPosition.y,0.0f));
	if (parameter.mat.GetPosition().y <= 0) parameter.isDead = true;
}

void EnemyVaristorBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyVaristorBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}