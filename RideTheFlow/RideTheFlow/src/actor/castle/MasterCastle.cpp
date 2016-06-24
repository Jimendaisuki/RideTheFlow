#include "MasterCastle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "castle.h"
#include "../../game/Random.h"
#include "CastleTop.h"
#include "../particle/CastleAdd.h"
#include "CastleBlock.h"
#include "../enemy/ArmyEnemy.h"
#include "../enemy/ShipEnemy.h"
#include "../../math/Math.h"
#include "../../UIactor/EnemyPoint.h"
#include "../NoShipArea.h"
MasterCastle::MasterCastle(IWorld& world, Vector3 position, bool spawnShip, bool title,float rotateY) :
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
mScale(45, 45, 45),
spawanArmyTimer(0.0f),
spawnShipTimer(0.0f),
mSpawnShip(spawnShip),
InvincibleTimer(0.0f),
mTitle(title)
{
	parameter.id = ACTOR_ID::MASTER_CASTLE_ACTOR;
	parameter.radius = 35;
	parameter.HP = 1;
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	if (!title)
	{
		world.UIAdd(UI_ID::ENEMY_POINT_UI, std::make_shared<EnemyPoint>(world, *this));
		world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
			parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f)
			, parameter.radius * 2, *this));
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<CastleTop>(world, parameter.mat.GetPosition() + Vector3(0, 100, 0), *this, rotateY));

	}
	testRnak = 1;
	parameter.height = Vector3(0.0f, 70.0f + 34 * testRnak, 0.0f);
	mRotateY = rotateY;
}

MasterCastle::~MasterCastle()
{

}

void MasterCastle::Update()
{
	if (!mTitle)
	{
		//各時間
		castleTime += Time::DeltaTime;
		//あたり判定
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
		//積み重なる城
		if (castleTime >= RankUpSecond&&mRank > 0)
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
				testRnak++;
				world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world,
					mPosition + Vector3(0.0f, parameter.radius * 2, 0.0f) + Vector3(0.0f, 20.0f*(Rank - mRank), 0.0f) + Vector3(0, 10 * (Rank - mRank), 0)
					, *this, Rank - mRank,mRotateY));
				parameter.height = Vector3(0.0f, 70.0f + 34.0f*testRnak, 0.0f);
				rankUpRagTimer = 0.0f;
				rankUpRag = false;
			}
		}
		//ステージに当たったら止まる
		if (downCastle)
		{
			//mPosition.y -= 50.0f*Time::DeltaTime;
		}
		downCastle = true;


		if (mSpawnShip)
		{
			spawnShipTimer += Time::DeltaTime;
			if (spawnShipTimer >= SpawnShipEnemyTime&&world.GetActorCount(ACTOR_ID::ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR) < SpawnMaxShipEnemey)
			{
				world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipEnemy>(world, parameter.mat.GetFront()*-3 + parameter.mat.GetUp() * 5 + mPosition));
				spawnShipTimer = 0.0f;
			}
		}
		else
		{
			spawanArmyTimer += Time::DeltaTime;
			if (spawanArmyTimer >= SpawnArmyEnemyTime&&world.GetActorCount(ACTOR_ID::ENEMY_ACTOR, ACTOR_ID::ARMY_ENEMY_ACTOR) < SpawnMaxArmyEnemy)
			{
				world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(world, parameter.mat.GetFront()*-2 + Vector3(0, 2, 0) + mPosition));
				spawanArmyTimer = 0.0f;
			}
		}

		//無敵時間
		if (!damage)
		{
			InvincibleTimer += Time::DeltaTime;
			if (CastleInvincibleTime <= InvincibleTimer)
			{
				InvincibleTimer = 0.0f;
				damage = true;
			}
		}
		//hpが0になったら死ぬ
		if (parameter.HP <= 0)
		{
			//がれきを飛ばす
			for (int i = 0; i < 8; i++){
				world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleBlock>(world, mPosition + Vector3(0.0f, Random::GetInstance().Range(-10.0f, 10.0f), 0.0f)));
			}
			parameter.isDead = true;
		}
	}
	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
}

void MasterCastle::Draw() const
{
	if (!mTitle)
	{
		Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, parameter.mat);
	}
	else
	{
		Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, parameter.mat);
		for (int i = 0; i <= 5; i++)
		{
			Vector3 Heght = mPosition + Vector3(0.0f, 17.0f * 2, 0.0f) + Vector3(0.0f, 30.0f*i, 0.0f);
			Matrix4 castleMat = Matrix4::Scale(30)*
				Matrix4::RotateY(mRotateY)*
				Matrix4::Translate(Heght);
			Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, castleMat);
		}
		Matrix4 topCastle = Matrix4::Scale(30)*
			Matrix4::RotateY(mRotateY)*
			Matrix4::Translate(mPosition + Vector3(0.0f, 17.0f * 2, 0.0f) + Vector3(0.0f, 30.0f*6, 0.0f));
		Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP2_MODEL, topCastle);
		Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP_MODEL, topCastle*Matrix4::Translate(Vector3(0, 40, 0)));
	}
}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL&&damage)
	{
		parameter.HP -= CastleDamegeTornado;
		damage = false;
	}
	if (colpara.colID == COL_ID::CASTLE_WIND_COL&&damage)
	{
		parameter.HP -= CastleDamegeWind;
		damage = false;
	}
}