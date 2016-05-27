#include "ShellBullet.h"

#include "../../world/IWorld.h"
#include"../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../castle/CastleParameter.h"
#include "../Collision.h"

#include "../../UIactor/Effect.h"

ShellBullet::ShellBullet(IWorld& world, Vector3 position, Vector3 toPoint, Actor& parent_) :
Actor(world),
time(0),
speed(3.0f),
distance(0, 0, 0),
mPosition(position),
mScale(1.0f),
coppyPosition(position),
mToPoint(toPoint)
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
ShellBullet::~ShellBullet()
{

}
void ShellBullet::Update()
{
	time += Time::DeltaTime * speed;
	if (coppyPosition.y < mToPoint.y)
	{
		float InitialVelocity = sqrt(2 * 9.8f*(mToPoint.y - coppyPosition.y) - mPosition.y);
		float vertexTime = InitialVelocity / 9.8f;
		//進行方向を計算
		vec = Vector3(
			distance.x / vertexTime * speed * Time::DeltaTime,
			0.0f,
			distance.z / vertexTime * speed * Time::DeltaTime);
		mPosition.y = InitialVelocity*time - 9.8f / 2.0f * pow(time, 2);
	}
	else
	{
		float vertexTime = sqrt((2 * (coppyPosition.y - mToPoint.y)) / 9.8f);
		//進行方向を計算
		vec = Vector3(
			distance.x / vertexTime * speed * Time::DeltaTime,
			0.0f,
			distance.z / vertexTime * speed * Time::DeltaTime);
		mPosition.y = -(1.0f / 2.0f) * 9.8f*pow(time, 2);
	}

	//移動
	mPosition += vec;

	if (parameter.mat.GetPosition().y <= -100) parameter.isDead = true;

	//マトリックス計算
	parameter.mat =
		Matrix4::Translate(mPosition + Vector3(0.0f, coppyPosition.y, 0.0f));
}

void ShellBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat.GetPosition(), 1.0f, parameter.mat.GetRotateDegree(), mScale, true);
}

void ShellBullet::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
	Effect::GetInstance().DamegeEffect(world, parent->GetParameter().mat.GetPosition(), other);
}