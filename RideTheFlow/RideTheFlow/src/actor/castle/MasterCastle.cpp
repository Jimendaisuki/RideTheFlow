#include "MasterCastle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../EnemyBullet.h"
#include "castle.h"
#include "../../game/Random.h"
#include "CastleParameter.h"

MasterCastle::MasterCastle(IWorld& world, Vector3 position) :
Actor(world),
attackTime(0),
castleTime(0),
attackRag(0),
arrowCount(0),
mRank(Rank),
mPosition(position),
playerMat(Matrix4::Identity),
mScale(30,30,30),
isLook(false)
{
    Vector2 side = Vector2(mScale.x, mScale.z) / 2;
    parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
	parameter.isDead = false;
	parameter.height = Vector3(0.0f,CastleHeight,0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	
	clor = 0.0f;
	toPoint = playerMat.GetPosition();
	//startPos = Matrix4::GetPosition(parameter.mat);
	//endPos = Matrix4::GetPosition(parameter.mat) + parameter.height * Vector3::Up;
}

MasterCastle::~MasterCastle()
{
	
}

void MasterCastle::Update()
{

	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);

	attackTime += Time::DeltaTime;
	castleTime += Time::DeltaTime;
	attackRag += Time::DeltaTime;
	if (castleTime >= RankUpSecond&&mRank>0)
	{
		mRank--;
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world,
			Vector3(mPosition.x, mPosition.y + (CastleHeight*(Rank - mRank)), mPosition.z)));
		castleTime = 0.0f;
	}

	if (attackTime >= SecondAttack&&attackRag >= 0.03f&&arrowCount < ArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= AttackRange&&
		abs(playerMat.GetPosition().y-mPosition.y)>=2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition,toPoint));
    if (arrowCount >= ArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	clor = 0.0f;
	if (isLook)
	{
		clor = 0.0f;
		toPoint = playerMat.GetPosition();
	}
	else
	{
		clor = 200.0f;
 		toPoint = Vector3::Direction(playerMat.GetPosition(),parameter.mat.GetPosition())*75;
	}
	isLook = true;
}

void MasterCastle::Draw() const
{
	//DrawFormatString(0, 128, GetColor(0, 0, 0), "startPosition   %f %f %f", Vector3::Direction(playerMat.GetPosition(), parameter.mat.GetPosition()).x, Vector3::Direction(playerMat.GetPosition(), parameter.mat.GetPosition()).y, Vector3::Direction(playerMat.GetPosition(), parameter.mat.GetPosition()).z);
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
	//DrawLine3D(Vector3::ToVECTOR(playerMat.GetPosition()), Vector3::ToVECTOR(parameter.mat.GetPosition()), GetColor(clor,0,0));
}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID==COL_ID::PLAYERTOCASTLELINE_CLOUD_COL)
	{
		isLook = false;
	}
}