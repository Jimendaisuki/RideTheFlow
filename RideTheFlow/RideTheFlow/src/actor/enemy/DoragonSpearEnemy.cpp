#include "DoragonSpearEnemy.h"

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
DoragonSpearEnemy::DoragonSpearEnemy(IWorld& world, Vector3 position,ShipEnemy& se,Actor& _parent) :
Actor(world),
coolTimer(0),
preparationTimer(0),
spearAttackTimer(0),
spearStopTimer(0),
mPosition(position),
mScale(2.0f),
playerWithin(false),
attackSpear(false),
endAttack(false)
{
	parameter.isDead = false;
	parameter.radius = 6.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	tubeMat=
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	parent=&_parent;
	mSe = &se;
}

DoragonSpearEnemy::~DoragonSpearEnemy()
{

}
void DoragonSpearEnemy::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_DORAGONSPEAR_WITHIN_COL);

	//槍のスタート
	startPos = mSe->GetShipEnemyPos().spearPos;
	//槍の終わり
	endPos = parameter.mat.GetLeft().Normalized() * 35 + mSe->GetShipEnemyPos().spearPos;


	coolTimer += Time::DeltaTime;
	if (playerWithin&&!attackSpear&&
		coolTimer >= DoragonSpearAttackTime)
	{
		preparationTimer += Time::DeltaTime;
		if (preparationTimer >= DoragonSpearWithinTime)
		{
			preparationTimer = 0.0f;
			coolTimer = 0.0f;
			attackSpear = true;
		}
	}
	else
	{
		preparationTimer = 0.0f;
	}
	//槍が出てくるとき
	if (attackSpear)
	{
		spearAttackTimer += (50.0f/DoragonSpearMaxTime)*Time::DeltaTime;
		if (spearAttackTimer >= 1.0f)
		{
			spearStopTimer += Time::DeltaTime;
			if (spearStopTimer >= DoragonSpearStopTime)
			{
				attackSpear = false;
				endAttack = true;
				spearAttackTimer = 1.0f;
				spearStopTimer = 0.0f;
			}
		}
	}
	//槍が戻るとき
	if (endAttack)
	{
		spearAttackTimer -= (1.0f)*Time::DeltaTime;
		if (spearAttackTimer <= 0.0f)
		{
			spearAttackTimer = 0.0f;
			endAttack = false;
		}
	}

	mPosition = Vector3::Lerp(startPos,endPos,spearAttackTimer);
	playerWithin = false;

	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
		Quaternion::RotateAxis(Vector3::Up,mSe->getRotate())*
		Matrix4::Translate(mPosition);

	tubeMat =
		Matrix4::Scale(mScale)*
		Quaternion::RotateAxis(Vector3::Up, mSe->getRotate())*
		Quaternion::RotateAxis(parameter.mat.GetFront(),-20)*
		Matrix4::Translate(mSe->GetShipEnemyPos().spearPos+
		parameter.mat.GetLeft().Normalized()*2+
		parameter.mat.GetUp().Normalized()*2);

	if (mSe->GetParameter().isDead)
	{
		parameter.isDead = true;
	}
}

void DoragonSpearEnemy::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::DORAGON_SPEAR_MODEL,parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::DORAGON_SPEAR_TUBE_MODEL, tubeMat);
	//DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition()) - parameter.mat.GetLeft().Normalized()*10.0f,
	//	Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*30.0f),
	//	parameter.radius, 20, 255, 255, FALSE);
	//////圏内
	//DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*30.0f),
	//	Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*70.0f), 
	//	parameter.radius, 20, 255, 255, FALSE);
}

void DoragonSpearEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYER_DORAGONSPEAR_WITHIN_COL)
	{
		playerWithin = true;
	}
}