#include "EnemyBullet.h"

#include "../Collision.h"
#include "../../world/IWorld.h"
#include"../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../castle/CastleParameter.h"
#include "../../math/Quaternion.h"
#include "../../UIactor/Effect.h"

EnemyBullet::EnemyBullet(IWorld& world, Vector3 position, Vector3 toPoint, Actor& parent_) :
Actor(world),
time(0),
speed(3.0f),
distance(0, 0, 0),
mPosition(position),
mScale(1.0f),
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
	distance = (mToPoint + mRandomTarget) - mPosition;

	parent = &parent_;
}
EnemyBullet::~EnemyBullet()
{

}
void EnemyBullet::Update()
{
	prevPosition = mPosition;

	time += Time::DeltaTime * speed;
	if (coppyPosition.y < mToPoint.y)
	{
		float InitialVelocity = sqrt(2 * 9.8f*(mToPoint.y - coppyPosition.y) - mPosition.y);
		float vertexTime = InitialVelocity / 9.8f;
		//�i�s�������v�Z
		vec = Vector3(
			distance.x / vertexTime * speed * Time::DeltaTime,
			0.0f,
			distance.z / vertexTime * speed * Time::DeltaTime);
		mPosition.y = InitialVelocity*time - 9.8f / 2.0f * pow(time, 2);
	}
	else
	{
		float vertexTime = sqrt((2 * (coppyPosition.y - mToPoint.y)) / 9.8f);
		//�i�s�������v�Z
		vec = Vector3(
			distance.x / vertexTime * speed * Time::DeltaTime,
			0.0f,
			distance.z / vertexTime * speed * Time::DeltaTime);
		mPosition.y = -(1.0f / 2.0f) * 9.8f*pow(time, 2);
	}

	//�ړ�
	mPosition += vec;

	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;

	mPosition += Vector3(0.0f, coppyPosition.y, 0.0f);
	//�i�s�����v�Z
	vec = mPosition - prevPosition;
	vec.Normalize();
	//�}�g���b�N�X�v�Z
	parameter.mat =
		Matrix4::Scale(mScale) *
		Quaternion::RotateAxis(Vector3::Cross(Vector3(0, 0, -1), vec).Normalized(), Vector3::Inner(Vector3(0,0,-1),vec)) *
		Matrix4::Translate(mPosition);
}

void EnemyBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);
}

void EnemyBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
	Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition(), other);
}