#include "MasterCastle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../enemy/EnemyBullet.h"
#include "castle.h"
#include "../../game/Random.h"
#include "CastleParameter.h"
#include "CastleTop.h"

MasterCastle::MasterCastle(IWorld& world, Vector3 position) :
Actor(world),
attackTime(0),
castleTime(0),
attackRag(0),
arrowCount(0),
mRank(Rank),
mPosition(position),
playerMat(Matrix4::Identity),
rankUp(false),
rankUpRag(false),
rankUpRagTimer(0),
mScale(45,45,45)
{
    parameter.radius = 35;
	parameter.isDead = false;
	parameter.height = Vector3(0.0f, 70.0f, 0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<CastleTop>(world,parameter.mat.GetPosition()+Vector3(0,100,0),*this));
}

MasterCastle::~MasterCastle()
{
	
}

void MasterCastle::Update()
{
	//各時間
	castleTime += Time::DeltaTime;
	//あたり判定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::STAGE_ACTOR, COL_ID::ARMYENEMY_STAGE_COL);
	//積み重なる城
	if (castleTime >= RankUpSecond&&mRank>0)
	{
		mRank--;
		rankUp = true;
		castleTime = 0.0f;
		rankUpRag = true;
	}
	else
	{
		rankUp = false;
	}
	//城が1秒後に出る
	if (rankUpRag)
	{
		rankUpRagTimer += Time::DeltaTime;
		if (rankUpRagTimer >= 1.0f)
		{
			world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world,
				mPosition + Vector3(0.0f, parameter.radius * 2, 0.0f) + Vector3(0.0f, 20.0f*(Rank - mRank), 0.0f) + Vector3(0, 10 * (Rank - mRank), 0)
				, *this));
			rankUpRagTimer = 0.0f;
			rankUpRag = false;
		}
	}
	//ステージに当たったら止まる
 	if (downCastle)
	{
		mPosition.y -= 50.0f*Time::DeltaTime;
	}
	downCastle = true;
	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
		Matrix4::Translate(mPosition);
}

void MasterCastle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, parameter.mat);}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::ARMYENEMY_STAGE_COL)
	{
		downCastle = false;
	}
}