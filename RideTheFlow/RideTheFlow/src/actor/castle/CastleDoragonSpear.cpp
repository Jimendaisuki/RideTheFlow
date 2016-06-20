#include "CastleDoragonSpear.h"

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
CastleDoragonSpear::CastleDoragonSpear(IWorld& world, Vector3 position, Castle& _castle,float rotateY) :
Actor(world),
coolTimer(0),
preparationTimer(0),
spearAttackTimer(0),
spearStopTimer(0),
mPosition(position),
tubePos(position),
mScale(2.8f),
playerWithin(false),
attackSpear(false),
endAttack(false)
{
	parameter.isDead = false;
	parameter.radius = 10.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(rotateY) *
		Matrix4::Translate(position);
	tubeMat = parameter.mat;

	mRotateY = rotateY;
	castle = &_castle;

	startPos = mPosition;
	endPos = parameter.mat.GetLeft().Normalized() * 60 + mPosition;
}

CastleDoragonSpear::~CastleDoragonSpear()
{

}
void CastleDoragonSpear::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_DORAGONSPEAR_WITHIN_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_DORAGONSPEAR_COL);

	//城の速度を足す
	startPos += castle->GetVelocity()*Time::DeltaTime;
	endPos += castle->GetVelocity()*Time::DeltaTime;


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
		spearAttackTimer += (50.0f / DoragonSpearMaxTime)*Time::DeltaTime;
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
	//城が死んだら自分も死ぬ
	if (castle->GetParameter().isDead)
	{
		parameter.isDead = true;
	}

	mPosition = Vector3::Lerp(startPos, endPos, spearAttackTimer);
	playerWithin = false;

	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
		Quaternion::RotateAxis(Vector3::Up,mRotateY)*
		Matrix4::Translate(mPosition);
	//筒にも速度を足す
	tubePos += castle->GetVelocity()*Time::DeltaTime;
	tubeMat =
		Matrix4::Scale(mScale)*
		Quaternion::RotateAxis(Vector3::Up, mRotateY)*
		Matrix4::Translate(tubePos);
}

void CastleDoragonSpear::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::DORAGON_SPEAR_MODEL, parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::DORAGON_SPEAR_TUBE_MODEL, tubeMat);
	//DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition()) - parameter.mat.GetLeft().Normalized()*5.0f,
	//	Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*15.0f),
	//	parameter.radius, 20, 255, 255, FALSE);

	////圏内
	//DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*15.0f),
	//	Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*35.0f), 
	//	parameter.radius, 20, 255, 255, FALSE);
}

void CastleDoragonSpear::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYER_DORAGONSPEAR_WITHIN_COL)
	{
		playerWithin = true;
	}
}