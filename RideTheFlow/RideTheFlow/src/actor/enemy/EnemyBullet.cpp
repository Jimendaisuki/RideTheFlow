#include "EnemyBullet.h"

#include "../Collision.h"
#include "../../world/IWorld.h"
#include"../../graphic/Model.h"
#include "../../time/Time.h"
#include "../castle/CastleParameter.h"

EnemyBullet::EnemyBullet(IWorld& world, Vector3 position,Vector3 toPoint) :
Actor(world),
time(0),
speed(3.0f),
distance(0, 0, 0),
mPosition(position),
coppyPosition(position),
mToPoint(toPoint)
{
	mRandomTarget = Vector3(GetRand(ArrowAccuracy * 2) - ArrowAccuracy,
		GetRand(ArrowAccuracy * 2) - ArrowAccuracy,
		GetRand(ArrowAccuracy * 2) - ArrowAccuracy);
	parameter.isDead = false;
	parameter.radius = 10.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	distance = (mToPoint + mRandomTarget)- mPosition;
}
EnemyBullet::~EnemyBullet()
{

}
void EnemyBullet::Update()
{
	time += Time::DeltaTime*speed;
	if (coppyPosition.y < mToPoint.y)
	{
		float InitialVelocity = sqrt(2 * 9.8f*(mToPoint.y - coppyPosition.y) - mPosition.y);
		float vertexTime = InitialVelocity / 9.8f;
		mPosition.x += distance.x / vertexTime * speed*Time::DeltaTime;
		mPosition.z += distance.z / vertexTime * speed*Time::DeltaTime;
		mPosition.y = (InitialVelocity*time - 9.8f / 2.0f * pow(time, 2));
	}
	else
	{
		float vertexTime = sqrt((2 * (coppyPosition.y - mToPoint.y)) / 9.8f);
		mPosition.y = -(1.0f / 2.0f) * 9.8f*pow(time, 2);
		mPosition.x += distance.x / vertexTime *speed*Time::DeltaTime;
		mPosition.z += distance.z / vertexTime *speed*Time::DeltaTime;
	}
	parameter.mat = Matrix4::Translate(mPosition+Vector3(0.0f,coppyPosition.y,0.0f));
	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;
}

void EnemyBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat);
}

void EnemyBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}