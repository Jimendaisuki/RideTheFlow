#include "VaristorBullet.h"

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
#include "../../math/Quaternion.h"
#include "../Player.h"
#include "../../sound/Sound.h"

VaristorBullet::VaristorBullet(IWorld& world, Vector3 position, Actor& parent_, float rotateY, float attackAngleZ,float InitialVec) :
Actor(world),
time(0),
speed(VaristorSpeed),
mPosition(position),
mScale(2.0f),
mRotateY(rotateY),
mRotateZ(attackAngleZ),
windVec(Vector3::Zero),
isWindCol(false),
seveVec(Vector3::Zero),
noDead(false),
noDeadTimer(0.0f),
mInitialVec(InitialVec)
{
	mRotateY += Random::GetInstance().Range(-VaristorArrowAccuracy, VaristorArrowAccuracy);
	mRotateZ += Random::GetInstance().Range(-VaristorArrowAccuracy, VaristorArrowAccuracy);
	parameter.id = ACTOR_ID::VARISTOR_BULLET_ACTOR;
	parameter.isDead = false;
	parameter.radius = 10.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	parent = &parent_;
	coppyPosition = position;
	Sound::GetInstance().PlaySEDuplicate(SE_ID::BALLISTA_FIRE_SE);
}
VaristorBullet::~VaristorBullet()
{
	parent = nullptr;
}
void VaristorBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::BULLET_WIND_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::ISLAND_ACTOR, COL_ID::BULLET_NOBULLETAREA_COL);
	time += VaristorSpeed*Time::DeltaTime;
	prevPosition = mPosition;
	//進行方向を計算
	vec = Vector3(
		mInitialVec*Math::Cos(mRotateY),
		mInitialVec*Math::Sin(mRotateZ + 20) - 9.8f*time,
		mInitialVec*Math::Sin(-mRotateY));
	//流れの向きを加味
	if (isWindCol)
		vec = Vector3::Lerp(vec, windVec, VaristorWindPercentage / 100.0f);
	//移動
	mPosition += vec*VaristorSpeed*Time::DeltaTime;
	if (parameter.mat.GetPosition().y <= -3600)
		parameter.isDead = true;

	//mPosition += Vector3(0.0f, coppyPosition.y, 0.0f);

	seveVec = mPosition - prevPosition;
	seveVec.Normalize();
	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale*VaristorBulletSize) *
		Quaternion::RotateAxis(Vector3::Cross(Vector3(0, 0, -1), seveVec).Normalized(), Vector3::Inner(Vector3(0, 0, -1), seveVec)) *
		Matrix4::Translate(mPosition);

	//流れの向きとフラグをリセット
	windVec = Vector3::Zero;
	isWindCol = false;


	//noDeadTimer += Time::DeltaTime;

	//if (noDeadTimer >= 1.0f)
	//{
	//	noDead = true;
	//	noDeadTimer = 10.0f;
	//}
}

void VaristorBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::BALLISTA_ARROW_MODEL, parameter.mat);
}

void VaristorBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::BULLET_WIND_COL)
	{
		windVec = colpara.colVelosity;
		isWindCol = true;
	}
	else if (colpara.colID == COL_ID::SPHERE_SPHERE_COL)
	{
		static_cast<Player*>(const_cast<Actor*>(&other))->Damage(*this,VaristorPower);
		parameter.isDead = true;
	}
	else if (colpara.colID == COL_ID::BULLET_NOBULLETAREA_COL)
	{
		parameter.isDead = true;
	}
}