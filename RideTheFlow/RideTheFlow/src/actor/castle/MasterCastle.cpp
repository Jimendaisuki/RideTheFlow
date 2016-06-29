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
mRank(Rank),
mPosition(position),
playerMat(Matrix4::Identity),
rankUp(false),
mScale(45*scale),
spawanArmyTimer(0.0f),
spawnShipTimer(0.0f),
mSpawnShip(spawnShip),
InvincibleTimer(0.0f),
breakSelect(BREAK_SELECT::TORNADO),
mTitle(title),
rankUpHeght(17.0f),
mScaleFloat(0.0f),
deadRagTimer(0.0f)
{
	parameter.id = ACTOR_ID::MASTER_CASTLE_ACTOR;
	parameter.radius = 35*scale;
	parameter.HP = MasterCastleHp;
	parameter.isDead = false;
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
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<CastleTop>(world, parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*2.0f, 0.0f), *this, rotateY,scale));

	}
	testRnak = 1;
	parameter.height = Vector3(0.0f, 70.0f + 34 * testRnak, 0.0f)*scale;
	mRotateY = rotateY;
	parent = this;
	mScaleFloat = scale;
	mTitleRank = titleRank;
	isDeadRag = false;
}

MasterCastle::~MasterCastle()
{

}

void MasterCastle::Update()
{
	if (!mTitle)
	{
		//�����蔻��
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
 		world.SetCollideSelect(shared_from_this(), ACTOR_ID::AIR_GUN_ACTOR, COL_ID::CASTLE_AIRGUN_COL);

		//�ςݏd�Ȃ��
		if (rankUp&&Rank >= testRnak)
		{
			testRnak++;
			mRank--;
			world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world,
				mPosition + Vector3(0.0f, parameter.radius, 0.0f)
				, *this, Rank - mRank, mRotateY,mScaleFloat));
			parameter.height = Vector3(0.0f, (70.0f + 34.0f*testRnak))*mScaleFloat;
			rankUp = false;
		}
		if (testRnak >= Rank)
		{
			noRankUp = true;
		}
		else
		{
			noRankUp = false;
		}
		if (mSpawnShip)
		{
			spawnShipTimer += Time::DeltaTime;
			if (spawnShipTimer >= SpawnShipEnemyTime&&world.GetActorCount(ACTOR_ID::SHIP_ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR) < SpawnMaxShipEnemey)
			{
				world.Add(ACTOR_ID::SHIP_ENEMY_ACTOR, std::make_shared<ShipEnemy>(world, parameter.mat.GetFront()*-3 + parameter.mat.GetUp() * 5 + mPosition));
				spawnShipTimer = 0.0f;
			}
		}
		else
		{
			spawanArmyTimer += Time::DeltaTime;
			if (spawanArmyTimer >= SpawnArmyEnemyTime&&world.GetActorCount(ACTOR_ID::ENEMY_ACTOR, ACTOR_ID::ARMY_ENEMY_ACTOR) < SpawnMaxArmyEnemy)
			{
				world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(world, parameter.mat.GetFront().Normalized()*-65.0f + Vector3(0, 15, 0) + mPosition));
				spawanArmyTimer = 0.0f;
			}
		}

		//���G����
		if (!damage)
		{
			InvincibleTimer += Time::DeltaTime;
			if (CastleInvincibleTime <= InvincibleTimer)
			{
				InvincibleTimer = 0.0f;
				damage = true;
			}
		}
		//hp��0�ɂȂ����玀��
		if (parameter.HP <= 0&&!isDeadRag)
		{
			//���ꂫ���΂�
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
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::K))
	{
		parameter.HP = 0.0f;
	}

	//�}�g���b�N�X�v�Z
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
		for (int i = 0; i <= mTitleRank; i++)
		{
			Vector3 Heght = Vector3(0.0f, 17.0f * 2, 0.0f) + Vector3(0.0f, 30.0f*i, 0.0f);
			Matrix4 castleMat = Matrix4::Scale(30.0f*mScaleFloat)*
				Matrix4::RotateY(mRotateY)*
				Matrix4::Translate(mPosition + Heght*Vector3(1.0f, mScaleFloat, 1.0f));
			Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, castleMat);
		}
		float height = parameter.radius*2.0f + 18.5f * 2 * mScaleFloat*(mTitleRank-1);
		Matrix4 topCastle = Matrix4::Scale(30.0f*mScaleFloat)*
			Matrix4::RotateY(mRotateY)*
			Matrix4::Translate(mPosition +Vector3(0.0f,height,0.0f));

		Matrix4 topCastle2 = Matrix4::Scale(30.0f*mScaleFloat)*
			Matrix4::RotateY(mRotateY)*
			Matrix4::Translate(mPosition + Vector3(0.0f, height, 0.0f)+Vector3(0.0f,40.0f*mScaleFloat,0.0f));
		Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP2_MODEL, topCastle);
		Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP_MODEL, topCastle2);
	}
}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL&&damage)
	{
		parameter.HP -= CastleDamegeWind;
		damage = false;
		if (parameter.HP <= 0)
			breakSelect = BREAK_SELECT::TORNADO;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, Vector3::Zero, DamageSmokeNum, DamageSmokeSize, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
	}
	if (colpara.colID == COL_ID::CASTLE_WIND_COL&&damage)
	{
		parameter.HP -= CastleDamegeWind;
		damage = false;
		if (parameter.HP <= 0)
			breakSelect = BREAK_SELECT::WIND_FLOW;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, Vector3::Zero, DamageSmokeNum, DamageSmokeSize, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);

	}
	if (colpara.colID == COL_ID::CASTLE_AIRGUN_COL&&damage)
	{
		parameter.HP -= CastleDamageWindBall;
		damage = false;
		if (parameter.HP <= 0)
			breakSelect = BREAK_SELECT::WIND_BALL;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, Vector3::Zero, DamageSmokeNum, DamageSmokeSize, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
	}
}