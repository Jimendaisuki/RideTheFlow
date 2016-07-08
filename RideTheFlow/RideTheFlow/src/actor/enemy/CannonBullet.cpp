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
#include "../Player.h"
#include "../../sound/Sound.h"

CannonBullet::CannonBullet(IWorld& world, Vector3 position, Actor& parent_,float rotateY,float attackAngleZ,float InitialVec,float Accuracy) :
Actor(world),
time(0),
speed(CannonSpeed),
mPosition(position),
mScale(1.0f),
mRotateY(rotateY),
mRotateZ(attackAngleZ),
noDead(false),
noDeadTimer(0.0f),
mInitialVec(InitialVec)
{
	mRotateY += Random::GetInstance().Range(-Accuracy, Accuracy);
	mRotateZ += Random::GetInstance().Range(-Accuracy, Accuracy);
	parameter.id = ACTOR_ID::CANNON_BULLET_ACTOR;
	parameter.isDead = false;
	parameter.radius = 10.0f*mScale.x;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	parent = &parent_;

	Sound::GetInstance().PlaySEDuplicate(SE_ID::CANON_FIRE_SE);

}
CannonBullet::~CannonBullet()
{
	parent = nullptr;
}
void CannonBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::BULLET_WIND_COL);
	world.SetCollideSelect(shared_from_this(), this->GetParameter().id, COL_ID::SPHERE_SPHERE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::ISLAND_ACTOR, COL_ID::BULLET_NOBULLETAREA_COL);
	time += CannonSpeed*Time::DeltaTime;
	//進行方向を計算
		vec = Vector3(
			mInitialVec*Math::Cos(mRotateY),
			mInitialVec*Math::Sin(mRotateZ) - 9.8f*time,
			mInitialVec*Math::Sin(-mRotateY));
	
	//移動
		mPosition += vec*CannonSpeed*Time::DeltaTime;
	//流れの向きを加味
		if (isWindCol)
			vec = Vector3::Lerp(vec, windVec, CannonWindPercentage / 100.0f);

		if (parameter.mat.GetPosition().y <= -3500) parameter.isDead = true;

	noDeadTimer += Time::DeltaTime;

	if (noDeadTimer >= 1.0f)
	{
		noDead = true;
		noDeadTimer = 10.0f;
	}
	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(Vector3(mScale*ConnonBulletSize)) *
		Matrix4::Translate(mPosition);
}

void CannonBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CANNON_BALL_MODEL, parameter.mat);
	DrawSphere3D(parameter.mat.GetPosition().ToVECTOR(), parameter.radius, 4, 1, 1, FALSE);
}

void CannonBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::BULLET_WIND_COL)
	{
		windVec = colpara.colVelosity;
		isWindCol = true;
	}
	else if (colpara.colID == COL_ID::SPHERE_SPHERE_COL)
	{
		//static_cast<Player*>(const_cast<Actor*>(&other))->Damage(CannonPower);
		parameter.isDead = true;
	}
	else if (colpara.colID == COL_ID::BULLET_NOBULLETAREA_COL&&noDead)
	{
		parameter.isDead = true;
	}
}