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

VaristorBullet::VaristorBullet(IWorld& world, Vector3 position,Actor& parent_, float rotateY, float attackAngleZ) :
Actor(world),
time(0),
speed(VaristorSpeed),
mPosition(position),
mScale(2.0f),
mRotateY(rotateY),
mRotateZ(attackAngleZ),
windVec(Vector3::Zero),
isWindCol(false)
{
	mRotateY += Random::GetInstance().Range(-VaristorArrowAccuracy, VaristorArrowAccuracy);
	mRotateZ += Random::GetInstance().Range(-VaristorArrowAccuracy, VaristorArrowAccuracy);
	parameter.id = ACTOR_ID::ENEMY_BULLET;
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
VaristorBullet::~VaristorBullet()
{

}
void VaristorBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::BULLET_WIND_COL);
	time += VaristorSpeed*Time::DeltaTime;
	//進行方向を計算
	vec = Vector3(
		VaristorInitialVelocity*Math::Cos(mRotateY),
		VaristorInitialVelocity*Math::Sin(mRotateZ+20) - 9.8f*time,
		VaristorInitialVelocity*Math::Sin(-mRotateY));
	//流れの向きを加味
	if (isWindCol)
		vec = Vector3::Lerp(vec, windVec, VaristorWindPercentage / 100.0f);
	//移動
	mPosition += vec*VaristorSpeed*Time::DeltaTime;
	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;

	mPosition += Vector3(0.0f, coppyPosition.y, 0.0f);

	vec.Normalize();
	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale) *
		Quaternion::RotateAxis(Vector3::Cross(Vector3(0, 0, -1), vec).Normalized(), Vector3::Inner(Vector3(0, 0, -1), vec)) *
		Matrix4::Translate(mPosition);

	//流れの向きとフラグをリセット
	windVec = Vector3::Zero;
	isWindCol = false;

	
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

	//parameter.isDead = true;
	//Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition(), other);
}