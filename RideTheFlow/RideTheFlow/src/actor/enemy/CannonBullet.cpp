#include "CannonBullet.h"

#include "../../world/IWorld.h"
#include"../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../castle/CastleParameter.h"
#include "../enemy/EnemyParameter.h"
#include "../Collision.h"

#include "../../UIactor/Effect.h"

CannonBullet::CannonBullet(IWorld& world, Vector3 position, Actor& parent_,float rotateY,float rotateZ) :
Actor(world),
time(0),
speed(0.5f),
distance(0, 0, 0),
mPosition(position),
mScale(1.0f),
coppyPosition(position),
mRotateY(rotateY),
mRotateZ(rotateZ)
{
	mRandomTarget = Vector3(GetRand(CannonShellAccuracy * 2) - CannonShellAccuracy,
		GetRand(CannonShellAccuracy * 2) - CannonShellAccuracy,
		GetRand(CannonShellAccuracy * 2) - CannonShellAccuracy);
	parameter.isDead = false;
	parameter.radius = 10.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	distance = (mToPoint + mRandomTarget) - mPosition;
	parent = &parent_;

	Matrix4 playerMat;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	Vector3 v = Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition()).Normalized();
}
CannonBullet::~CannonBullet()
{

}
void CannonBullet::Update()
{
	time += Time::DeltaTime * speed;
	//進行方向を計算
		vec = Vector3(
			CannonInitialVelocity*Math::Cos(mRotateY),
			CannonInitialVelocity*Math::Sin(mRotateZ) - 9.8f*time,
			CannonInitialVelocity*Math::Sin(-mRotateY));
	//移動
	mPosition += vec;




	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;

	//マトリックス計算
	parameter.mat =
		Matrix4::Translate(mPosition);
}

void CannonBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);

}

void CannonBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
	Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition(), other);
}