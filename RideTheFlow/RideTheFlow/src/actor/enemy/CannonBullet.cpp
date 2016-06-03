#include "CannonBullet.h"

#include "../../world/IWorld.h"
#include"../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../castle/CastleParameter.h"
#include "../enemy/EnemyParameter.h"
#include "../Collision.h"
#include "../../game/Random.h"
#include "../../UIactor/Effect.h"

CannonBullet::CannonBullet(IWorld& world, Vector3 position, Actor& parent_,float rotateY,float attackAngleZ) :
Actor(world),
time(0),
speed(CannonSpeed),
mPosition(position),
mScale(1.0f),
mRotateY(rotateY),
mRotateZ(attackAngleZ)
{
	mRotateY += Random::GetInstance().Range(-CannonShellAccuracy, CannonShellAccuracy);
	mRotateZ += Random::GetInstance().Range(-CannonShellAccuracy, CannonShellAccuracy);
	parameter.isDead = false;
	parameter.radius = 10.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	parent = &parent_;

}
CannonBullet::~CannonBullet()
{

}
void CannonBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::BULLET_WIND_COL);
	time += CannonSpeed*Time::DeltaTime;
	//進行方向を計算
		vec = Vector3(
			CannonInitialVelocity*Math::Cos(mRotateY),
			CannonInitialVelocity*Math::Sin(mRotateZ) - 9.8f*time,
			CannonInitialVelocity*Math::Sin(-mRotateY));
	
	//移動
		mPosition += vec*CannonSpeed*Time::DeltaTime;
	//流れの向きを加味
		if (isWindCol)
			vec = Vector3::Lerp(vec, windVec, CannonWindPercentage / 100.0f);

	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;


	//マトリックス計算
	parameter.mat =
		Matrix4::Translate(mPosition);
}

void CannonBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CANNON_BALL_MODEL, parameter.mat);
}

void CannonBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::BULLET_WIND_COL)
	{
		windVec = colpara.colVelosity;
		isWindCol = true;
	}

	//parameter.isDead = true;
	//Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition(), other);
}