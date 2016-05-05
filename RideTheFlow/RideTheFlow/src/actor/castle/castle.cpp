#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

#include "../EnemyBullet.h"
#include "../EnemyGunBullet.h"
#include "../EnemyVaristorBullet.h"
#include "../ParachuteBombBullet.h"

#include"CastleParameter.h"

Castle::Castle(IWorld& world, Vector3 position) :
Actor(world),
arrowCount(0),
attackRag(0.0f),
playerMat(Matrix4::Identity),
mPosition(position),
randomTarget(0,0,0),
endPos(0,0,0),
startPos(0,0,0),
mScale(30,30,30)
{
	//MV1_REF_POLYGONLIST castleModel= MV1GetReferenceMesh(Model::GetInstance().GetHandle(MODEL_ID::CASTLE_MODEL), -1, FALSE);

	//float castleMin = sqrtf(castleModel.MinPosition.x * castleModel.MinPosition.x + castleModel.MinPosition.z * castleModel.MinPosition.z);;
	//float castleMax = sqrtf(castleModel.MaxPosition.x * castleModel.MaxPosition.x + castleModel.MaxPosition.z * castleModel.MaxPosition.z);;
	//parameter.radius=Math::Max(castleMin, castleMax);
	//parameter.height = castleModel.MaxPosition.y-castleModel.MinPosition.y;
	Vector2 side = Vector2(mScale.x, mScale.z) / 2;
	parameter.isDead = false;
	parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
	parameter.height = Vector3(0.0f,30.0f,0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	startPos = Matrix4::GetPosition(parameter.mat);
	endPos = startPos + parameter.height;
}

Castle::~Castle()
{

}

void Castle::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	attackRag += Time::DeltaTime;
	mAttackTime += Time::DeltaTime;
	if (mAttackTime >= SecondAttack&&attackRag >= 0.03f&&arrowCount < ArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= AttackRange&&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		randomTarget = Vector3(GetRand(ArrowAccuracy * 2) - ArrowAccuracy,
			GetRand(ArrowAccuracy * 2) - ArrowAccuracy,
			GetRand(ArrowAccuracy * 2) - ArrowAccuracy);
		//world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyGunBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(1, 1, 1), randomTarget, 2.0f));
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyVaristorBullet>(world,mPosition));
		if (arrowCount >= ArrowNumber)
		{
			arrowCount = 0;
			mAttackTime = 0.0f;
		}

	}
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
	//DrawCapsule3D(startPos, endPos, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	//DrawLine3D(startPos, endPos, GetColor(255, 0, 0));

	//DrawCube3D(
	//	Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) / 2, 
	//	Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) / 2, 
	//	color, 
	//	GetColor(0, 0, 0), 
	//	false);
	//DrawFormatString(10, 100, GetColor(255, 255, 255), "CastlePos	: %f %f %f", Matrix4::GetPosition(parameter.mat).x, Matrix4::GetPosition(parameter.mat).y, Matrix4::GetPosition(parameter.mat).z);
	//DrawFormatString(10, 120, GetColor(255, 255, 255), "CastleScale	: %f %f %f", Matrix4::GetScale(parameter.mat).x, Matrix4::GetScale(parameter.mat).y, Matrix4::GetScale(parameter.mat).z);
	//if (isHit)
	//{
	//	DrawFormatString(10, 400, GetColor(255, 255, 255), "Hit");
	//}
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}