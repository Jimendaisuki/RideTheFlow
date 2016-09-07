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
#include "../particle/BreakCastle.h"
#include "../../input/Keyboard.h"
#include "../../sound/Sound.h"
#include "../../WindAndTornadoSetting.h"

MasterCastle::MasterCastle(IWorld& world, Vector3 position, float rotateY, float scale, bool spawnShip, bool title, int titleRank) :
Actor(world),
breakSelect(BREAK_SELECT::TORNADO),
mPosition(position),
mScale(45 * scale),
mScaleFloat(scale),
mRotateY(rotateY),
InvincibleTimer(0.0f),
deadRagTimer(0.0f),
testRnak(1),
mRank(0),
mTitleRank(titleRank),
mTitle(title),
mSpawnShip(spawnShip),
rankUp(false),
isDeadRag(false),
spawnEnemyFlag(false)
{
	parameter.id = ACTOR_ID::MASTER_CASTLE_ACTOR;
	parameter.radius = 35 * scale;
	parameter.HP = MasterCastleHp;
	parameter.isDead = false;
	parameter.height = Vector3(0.0f, 70.0f, 0.0f)*scale;
	parameter.mat =
		Matrix4::Scale(mScale*scale) *
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
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<CastleTop>(world, parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*2.0f, 0.0f), *this, rotateY, scale));
	}
	parent = this;

	gauge.Initialize(parameter.HP, parameter.mat.GetPosition());

	for (auto& castle : castles)
		castle = nullptr;
}

MasterCastle::~MasterCastle()
{

}

void MasterCastle::Update()
{
	if (!mTitle)
	{
		//あたり判定
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::AIR_GUN_ACTOR, COL_ID::CASTLE_AIRGUN_COL);

		castlesList.remove_if([](Castle* castle){return castle->GetDeadRagFlag(); });
		int count = 0;
		for (auto& i : castlesList)
		{
			if (i != nullptr)
			{
				i->SetRank(count);
				count++;
			}
		}
		//積み重なる城
		if (rankUp&&Rank > castlesList.size())
		{
			mRank++;
			auto castle = std::make_shared<Castle>(world,
				mPosition + Vector3(0.0f, parameter.radius, 0.0f)
				, *this, mRank, mRotateY, mScaleFloat);

			world.Add(ACTOR_ID::CASTLE_ACTOR, castle);
			castlesList.push_front(castle.get());
			rankUp = false;
		}


		//これ以上積みあがれるか
		if (testRnak >= Rank)
		{
			noRankUp = true;
		}
		else
		{
			noRankUp = false;
		}

		//敵を出現
		if (spawnEnemyFlag)
		{
			if (mSpawnShip)
			{
				world.Add(ACTOR_ID::SHIP_ENEMY_ACTOR, std::make_shared<ShipEnemy>(world,
					parameter.mat.GetFront()*-3 + parameter.mat.GetUp() * 5 + mPosition));
			}
			else
			{
				world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(world,
					(parameter.mat.GetFront().Normalized()*-65.0f + Vector3(0, 15, 0)*mScaleFloat) + mPosition));
			}
			spawnEnemyFlag = false;
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
		if (parameter.HP <= 0 && !isDeadRag)
		{
			//がれきを飛ばす
			world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::MASTER_CASTLE, breakSelect));
			Sound::GetInstance().PlaySE(SE_ID::CASTLE_BREAK_SE);
			isDeadRag = true;
		}

		if (isDeadRag)
		{
			deadRagTimer += Time::DeltaTime;
			if (deadRagTimer >= 0.5f)
				parameter.isDead = true;
		}
	}

	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);

	gauge.Update(parameter.HP, parameter.mat.GetPosition());
}

void MasterCastle::Draw() const
{
	if (!mTitle)
	{
		Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, parameter.mat);
		gauge.Draw();
	}
	else
	{
		Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, parameter.mat);
		for (int i = 0; i <= mTitleRank; i++)
		{
			Vector3 Heght = Vector3(0.0f, 17.0f * 2, 0.0f) + Vector3(0.0f, 30.0f*i, 0.0f);
			Matrix4 castleMat = Matrix4::Scale(30.0f*mScaleFloat)*
				Matrix4::RotateY(mRotateY)*
				Matrix4::Translate(mPosition + Heght*Vector3(1.0f, mScaleFloat, 1.0f));
			Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, castleMat);
		}
		float height = parameter.radius*2.0f + 18.5f * 2 * mScaleFloat*(mTitleRank - 1);
		Matrix4 topCastle = Matrix4::Scale(30.0f*mScaleFloat)*
			Matrix4::RotateY(mRotateY)*
			Matrix4::Translate(mPosition + Vector3(0.0f, height, 0.0f));

		Matrix4 topCastle2 = Matrix4::Scale(30.0f*mScaleFloat)*
			Matrix4::RotateY(mRotateY)*
			Matrix4::Translate(mPosition + Vector3(0.0f, height, 0.0f) + Vector3(0.0f, 40.0f*mScaleFloat, 0.0f));
		Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP2_MODEL, topCastle);
		Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP_MODEL, topCastle2);
	}
}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL&&damage)
	{
		DamageTornad(mPosition);
	}
	if (colpara.colID == COL_ID::CASTLE_WIND_COL&&damage)
	{
		DamageWind(mPosition);
	}
	if (colpara.colID == COL_ID::CASTLE_AIRGUN_COL&&damage)
	{
		DamageAirGun(mPosition);
	}
}

void MasterCastle::DamageWind(Vector3 position)
{
	if (damage)
	{
		damage = false;
		parameter.HP -= CastleDamegeWind;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, position, DamageSmokeNum, DamageSmokeSizeCastle, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
		if (parameter.HP <= 0)
			breakSelect = BREAK_SELECT::WIND_FLOW;
		else
			world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, position, CASTLE_SELECT::MASTER_CASTLE, BREAK_SELECT::DAMAGE));
	}
}
void MasterCastle::DamageTornad(Vector3 position)
{
	if (damage)
	{
		damage = false;
		parameter.HP -= CastleDamegeTornado;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, position, DamageSmokeNum, DamageSmokeSizeCastle, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
		if (parameter.HP <= 0)
			breakSelect = BREAK_SELECT::TORNADO;
		else
			world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, position, CASTLE_SELECT::MASTER_CASTLE, BREAK_SELECT::DAMAGE));
	}
}
void MasterCastle::DamageAirGun(Vector3 position)
{
	if (damage)
	{
		damage = false;
		parameter.HP -= CastleDamageWindBall;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, position, DamageSmokeNum, DamageSmokeSizeCastle, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
		if (parameter.HP <= 0)
			breakSelect = BREAK_SELECT::WIND_BALL;
		else
			world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, position, CASTLE_SELECT::MASTER_CASTLE, BREAK_SELECT::DAMAGE));
	}
}