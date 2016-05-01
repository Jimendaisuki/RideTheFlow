#include "EnemyVaristorBullet.h"

#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"

//çUåÇÇÃê∏ìx(êîílÇ™è¨Ç≥Ç¢ÇŸÇ«çÇê∏ìx)
const float ArrowAccuracy = 15.0f;

EnemyVaristorBullet::EnemyVaristorBullet(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
time(0),
speed(3.0f),
distance(0, 0, 0),
mPosition(position),
coppyPosition(position)
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

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
		float InitialVelocity = sqrt(2 * 9.8f*(playerMat.GetPosition().y - coppyPosition.y) - mPosition.y);
		float vertexTime = InitialVelocity / 9.8f;
		mPosition.x += distance.x / vertexTime * speed*Time::DeltaTime;
		mPosition.z += distance.z / vertexTime * speed*Time::DeltaTime;
		mPosition.y = (InitialVelocity*time - 9.8f / 2.0f * pow(time, 2));
	}
	else
	{
		float vertexTime = sqrt((2 * (coppyPosition.y - playerMat.GetPosition().y)) / 9.8f);
		mPosition.y = -(1.0f / 2.0f) * 9.8f*pow(time, 2);
		mPosition.x += distance.x / vertexTime *speed*Time::DeltaTime;
		mPosition.z += distance.z / vertexTime *speed*Time::DeltaTime;
	}
	parameter.mat = Matrix4::Translate(mPosition+Vector3(0.0f,coppyPosition.y,0.0f));
	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;
}

void EnemyVaristorBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyVaristorBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}