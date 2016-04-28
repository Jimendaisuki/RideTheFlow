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

Castle::Castle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale, float secondAttack, float attackRange, int arrowNumber, float arrowAccuracy,float attackTime) :
Actor(world),
mSecondAttack(secondAttack),
mAttackRange(attackRange),
mArrowAccuracy(arrowAccuracy),
mArrowNumber(arrowNumber),
arrowCount(0),
attackRag(0.0f),
mAttackTime(attackTime),
playerMat(Matrix4::Identity),
mPosition(position),
randomTarget(0,0,0),
endPos(0,0,0),
startPos(0,0,0)
{

	//MV1_REF_POLYGONLIST castleModel= MV1GetReferenceMesh(Model::GetInstance().GetHandle(MODEL_ID::CASTLE_MODEL), -1, FALSE);

	//float castleMin = sqrtf(castleModel.MinPosition.x * castleModel.MinPosition.x + castleModel.MinPosition.z * castleModel.MinPosition.z);;
	//float castleMax = sqrtf(castleModel.MaxPosition.x * castleModel.MaxPosition.x + castleModel.MaxPosition.z * castleModel.MaxPosition.z);;
	//parameter.radius=Math::Max(castleMin, castleMax);
	//parameter.height = castleModel.MaxPosition.y-castleModel.MinPosition.y;
	Vector2 side = Vector2(scale.x, scale.z) / 2;
	parameter.isDead = false;
	parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
	parameter.height = 30.0f;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	startPos = Matrix4::GetPosition(parameter.mat);
	endPos = startPos + Vector3(0.0f, parameter.height, 0.0f);
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
	if (mAttackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(),mPosition)<=mAttackRange)
	{
		attackRag = 0.0f;
		arrowCount++;
		randomTarget = Vector3(GetRand(mArrowAccuracy * 2) - mArrowAccuracy,
			GetRand(mArrowAccuracy * 2) - mArrowAccuracy,
			GetRand(mArrowAccuracy * 2) - mArrowAccuracy);
		//world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyGunBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(1, 1, 1), randomTarget, 2.0f));
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyVaristorBullet>(world,mPosition, Vector3(0, 0, 0), Vector3(5, 5, 5), randomTarget));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			mAttackTime = 0.0f;
		}

	}
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
	DrawCapsule3D(startPos, endPos, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

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
	//parameter.isDead = true;
}