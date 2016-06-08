#include "CastleTop.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "CastleCannon.h"
#include"../enemy/EnemyBullet.h"
#include "../../math/Math.h"
#include"CastleParameter.h"

CastleTop::CastleTop(IWorld& world, Vector3 position, MasterCastle& mc) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position),
mScale(30, 30, 30),
castleDown(true),
noColTimer(0),
noCol(false)
{
	//MV1_REF_POLYGONLIST castleModel= MV1GetReferenceMesh(Model::GetInstance().GetHandle(MODEL_ID::CASTLE_MODEL), -1, FALSE);

	//float castleMin = sqrtf(castleModel.MinPosition.x * castleModel.MinPosition.x + castleModel.MinPosition.z * castleModel.MinPosition.z);;
	//float castleMax = sqrtf(castleModel.MaxPosition.x * castleModel.MaxPosition.x + castleModel.MaxPosition.z * castleModel.MaxPosition.z);;
	//parameter.radius=Math::Max(castleMin, castleMax);
	//parameter.height = castleModel.MaxPosition.y-castleModel.MinPosition.y;
	Vector2 side = Vector2(mScale.x, mScale.z) / 2;
	parameter.isDead = false;
	parameter.radius = 35;
 	parameter.height = Vector3(0.0f, 30.0f, 0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	mMc = &mc;
}

CastleTop::~CastleTop()
{

}

void CastleTop::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::CASTLE_CASTLE_COL);
	//城に当たったら落ちるのを止める
	if (castleDown)
	{
		velocity.y -= 200.0f*Time::DeltaTime;
		if (velocity.y <= -200.0f)
			velocity.y = -200.0f;
	}
	else if (mMc->castleRankUp())
	{
		//城が出現する前にジャンプ
		velocity.y += 170.0f;
		noCol = true;
	}
	else
	{
		velocity = 0;
	}
	//ジャンプする瞬間はあたり判定無効
	if (noCol)
	{
		noColTimer += Time::DeltaTime;
		if (noColTimer >= 0.5f)
			noCol = false;
	}
	castleDown = true;
	mPosition += velocity*Time::DeltaTime;
	//マスターが壊れたら自分も壊れる
	if (mMc->GetParameter().isDead)
	{
		parameter.isDead = true;
	}
	parameter.mat = Matrix4::Scale(mScale)*
		Matrix4::Translate(mPosition);
}

void CastleTop::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP2_MODEL, parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP_MODEL, parameter.mat*Matrix4::Translate(Vector3(0,40,0)));
}

void CastleTop::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::CASTLE_CASTLE_COL&&colpara.colFlag&&!noCol)
	{
		castleDown = false;
	}
}