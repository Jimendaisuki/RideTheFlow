#include "EnemyBullet.h"

#include "Collision.h"
#include "../world/IWorld.h"
#include"../graphic/Model.h"
#include "../time/Time.h"
#include "../actor/castle/CastleParameter.h"
#include "../math/Math.h"

EnemyBullet::EnemyBullet(IWorld& world, Vector3 position,Vector3 toPoint) :
Actor(world),
time(0),
speed(3.0f),
distance(0, 0, 0),
mPosition(position),
mScale(3.0f),
coppyPosition(position),
mToPoint(toPoint),
rotate(Vector3::Zero)
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
	time += Time::DeltaTime * speed;
	if (coppyPosition.y < mToPoint.y)
	{
		float InitialVelocity = sqrt(2 * 9.8f*(mToPoint.y - coppyPosition.y) - mPosition.y);
		float vertexTime = InitialVelocity / 9.8f;
		//進行方向を計算
		vec = Vector3(
			distance.x / vertexTime * speed * Time::DeltaTime,
			InitialVelocity*time - 9.8f / 2.0f * pow(time, 2),
			distance.z / vertexTime * speed * Time::DeltaTime);
	}
	else
	{
		float vertexTime = sqrt((2 * (coppyPosition.y - mToPoint.y)) / 9.8f);
		//進行方向を計算
		vec = Vector3(
			distance.x / vertexTime * speed * Time::DeltaTime,
			-(1.0f / 2.0f) * 9.8f*pow(time, 2),
			distance.z / vertexTime * speed * Time::DeltaTime);
	}

	//移動
	mPosition += vec;

	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;


	//進行方向を分ける
	Vector3 vXY = Vector3(vec.x, vec.y, 0.0f).Normalized();
	Vector3 vXZ = Vector3(vec.x, 0.0f, vec.z).Normalized();
	Vector3 vYZ = Vector3(0.0f, vec.y, vec.z).Normalized();
	//回転計算
	//rotate.x = Math::Degree(Math::Atan2(vYZ.z, vYZ.y));
	rotate.y = Math::Degree(Math::Atan2(vXZ.x, vXZ.z));
	//rotate.z = Math::Degree(Math::Atan2(vXY.y, vXY.x));

	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::Translate(mPosition + Vector3(0.0f, coppyPosition.y, 0.0f));
}

void EnemyBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat.GetPosition(), 1.0f, rotate, mScale, true);
}

void EnemyBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}