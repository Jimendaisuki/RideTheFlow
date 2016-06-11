#include "SoldierEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "EnemyBullet.h"
#include "../../math/Math.h"
#include "../Player.h"
#include "../castle/castle.h"
#include "ShipEnemy.h"
#include "../castle/CastleParameter.h"

SoldierEnemy::SoldierEnemy(IWorld& world, Vector3 position, Castle& castle, float rotateY) :
Actor(world),
playerMat(Matrix4::Identity),
cameraMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
mPosition(position),
toPoint(Vector3::Zero),
mRotateY(rotateY),
isLook(true)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::RotateY(rotateY),
		Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;
	mCastle = &castle;

}
SoldierEnemy::~SoldierEnemy()
{

}
void SoldierEnemy::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	world.EachActor(ACTOR_ID::CAMERA_ACTOR, [&](const Actor& other){
		cameraMat = other.GetParameter().mat;
	});
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::STAGE_ACTOR, COL_ID::ARMYENEMY_STAGE_COL);

	//プレイヤーが見えているかどうか
	if (mCastle->isLookPlayer())
	{
		mArrowNumber = CastleSoldierNumber;
		mSecondAttack = CastleSoldierSecondAttack;
	}
	else
	{
		mArrowNumber = CastleSoldierNotLookAttack;
		mSecondAttack = CastleSoldierNotLookSecondAttack;
	}


	//ダッシュ中以外はカメラの前に矢を放つ
	if (tp.dashFlag)
	{
		toPoint = playerMat.GetPosition();
	}
	else
	{
		toPoint = playerMat.GetFront().Normalized()*cameraFrontAttack + playerMat.GetPosition();
	}

	isLook = true;

	//攻撃
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (attackTime >= mSecondAttack&&attackRag >= 0.3f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= CastleSoldierAttackRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, toPoint, *this));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	mPosition += mCastle->GetVelocity()*Time::DeltaTime;
	parameter.mat =
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
}
void SoldierEnemy::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), 10, 20, 255, 255, FALSE);
}
void SoldierEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::ARMYENEMY_STAGE_COL)
	{
		mPosition = colpara.colPos;
	}
}