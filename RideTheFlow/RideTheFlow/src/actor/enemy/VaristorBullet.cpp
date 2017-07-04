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

VaristorBullet::VaristorBullet(IWorld& world, Vector3 position, Actor& parent_, float rotateY, float attackAngleZ, float InitialVec, float Accuracy) :
Actor(world),
mPosition(position),
seveVec(Vector3::Zero),
windVec(Vector3::Zero),
Tornadleft(Vector3::Zero),
mRotateY(rotateY),
mRotateZ(attackAngleZ),
mInitialVec(InitialVec),
speed(VaristorSpeed),
time(0),
mScale(2.0f),
isWindCol(false),
isColFastFlag(true),
isColTornad(false)
{
	mRotateY += Random::GetInstance().Range(-Accuracy, Accuracy);
	mRotateZ += Random::GetInstance().Range(-Accuracy, Accuracy);
	parameter.id = ACTOR_ID::VARISTOR_BULLET_ACTOR;
	parameter.isDead = false;
	parameter.radius = 10.0f*mScale.x;
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
	time += VaristorSpeed*Time::GetInstance().deltaTime();
	prevPosition = mPosition;
	//進行方向を計算
	vec = Vector3(
		mInitialVec*Math::Cos(mRotateY),
		mInitialVec*Math::Sin(mRotateZ + 20) - 9.8f*time,
		mInitialVec*Math::Sin(-mRotateY));
	//流れの向きを加味
	if (isWindCol)
		vec = Vector3::Lerp(vec, windVec, VaristorWindPercentage / 100.0f);
	//竜巻
	if (isColTornad)
	{
		if (isColFastFlag)
		{
			Vector3 pos = mPosition;
			pos += vec;
			vec = pos - prevPosition;
			vec.Normalize();
			Tornadleft = -Vector3::Cross(Vector3(0, -1, 0), vec).Normalized()*30.0f;
			isColFastFlag = false;
		}
		vec = Vector3::Lerp(vec, Tornadleft, 75.0f/100.0f);
	}

	//移動
	mPosition += vec*VaristorSpeed*Time::GetInstance().deltaTime();
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

}

void VaristorBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::BALLISTA_ARROW_MODEL, parameter.mat);
	//DrawSphere3D(parameter.mat.GetPosition().ToVECTOR(), parameter.radius, 4, 1, 1, FALSE);
}

void VaristorBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::BULLET_WIND_COL)
	{
		windVec = colpara.colVelosity;
		isWindCol = true;
	}
	else if (colpara.colID == COL_ID::BULLET_NOBULLETAREA_COL)
	{
		parameter.isDead = true;
	}
	else if (colpara.colID == COL_ID::TORNAD_BULLET_COL)
	{
		isColTornad = true;
	}
}