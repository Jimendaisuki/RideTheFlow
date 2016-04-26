#include "EnemyBullet.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../input/Keyboard.h"
#include <math.h>
EnemyBullet::EnemyBullet(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float initialVelocity) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position),
time(0.0f),
mInitialVelocity(initialVelocity),
coppyPosition(position),
angle(0),
speed(4.5f)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	mDirection = Vector3::Direction(mPosition, playerMat.GetPosition());
	
	angle = atan2(playerMat.GetPosition().y - mPosition.y,playerMat.GetPosition().x - mPosition.x);
}
EnemyBullet::~EnemyBullet()
{
	
}
void EnemyBullet::Update()
{
	time += Time::DeltaTime*speed;
	//mPosition.z = mInitialVelocity*cos(angle)*time;
	mPosition.x = mInitialVelocity*cos(angle)*time;
	mPosition.y = mInitialVelocity*sin(angle)*time - 1.0f / 2.0f*9.8f*pow(time, 2);

	parameter.mat = Matrix4::Translate(Vector3(mPosition.x,mPosition.y,mPosition.z)+coppyPosition);
}

void EnemyBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat.GetPosition());
}

void EnemyBullet::OnCollide(Actor& other, CollisionParameter colpara)
{

}