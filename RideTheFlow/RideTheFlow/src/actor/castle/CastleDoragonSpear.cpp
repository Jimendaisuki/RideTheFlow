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
#include "../Player.h"
CastleDoragonSpear::CastleDoragonSpear(IWorld& world, Vector3 position, Actor& _parent, float rotateY) :
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
endAttack(false),
playerWithinTimer(0.0f)
{
	parameter.id = ACTOR_ID::DORAGONSPEAR_ACTOR;
	parameter.isDead = false;
	parameter.radius = 20.0f;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(rotateY) *
		Matrix4::Translate(position);
	tubeMat = parameter.mat;

	mRotateY = rotateY;
	parent = &_parent;
	castle = static_cast<Castle*>(const_cast<Actor*>(&_parent));
	startPos = mPosition;
	endPos = parameter.mat.GetLeft().Normalized() * 60 + mPosition;
}

CastleDoragonSpear::~CastleDoragonSpear()
{

}
void CastleDoragonSpear::Update()
{
	Actor* player;
	Matrix4 playerMat;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		player = const_cast<Actor*>(&other);
	});

	////城の速度を足す
	startPos += castle->GetVelocity();
	endPos += castle->GetVelocity();


	if (Vector3::Distance(playerMat.GetPosition(), parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*50.0f) <=
		parameter.radius + 8.0f)
	{
		playerWithin = true;
	}
	else
	{
		playerWithin = false;
	}


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
		static_cast<Player*>(const_cast<Actor*>(player))->ColSpear(parent);
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

	////マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
	//筒にも速度を足す
	tubePos += castle->GetVelocity();
	tubeMat =
		Matrix4::Scale(mScale)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(tubePos);
}

void CastleDoragonSpear::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::DORAGON_SPEAR_MODEL, parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::DORAGON_SPEAR_TUBE_MODEL, tubeMat);
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*50.0f), parameter.radius, 20, 1, 1, FALSE);
	DrawLine3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetUp() * 100), 255);
	//DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition()) - parameter.mat.GetLeft().Normalized()*10.0f,
	//	Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*30.0f),
	//	parameter.radius, 20, 255, 255, FALSE);
	//////圏内
	//DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*30.0f),
	//	Vector3::ToVECTOR(parameter.mat.GetPosition() + parameter.mat.GetLeft().Normalized()*70.0f), 
	//	parameter.radius, 20, 255, 255, FALSE);
}

void CastleDoragonSpear::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::SPHERE_SPHERE_COL)
	{

	}
}