#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "CastleCannon.h"
#include "CastleDoragonSpear.h"
#include "../enemy/SoldierEnemy.h"
#include"CastleParameter.h"
#include "CastleBlock.h"
#include "../../game/Random.h"
#include "../particle/CastleAdd.h"
#include "MasterCastle.h"
#include "../../input/Keyboard.h"
#include "../NoShipArea.h"
#include "CastleVaristor.h"
#include "../../math/Quaternion.h"
#include "../../sound/Sound.h"
#include "../../WindAndTornadoSetting.h"

Castle::Castle(IWorld& world, Vector3 position, Actor& _parent, int rank, float rotateY,float scale) :
Actor(world),
mPosition(position),
sevePos(position),
prevPos(Vector3::Zero),
velocity(Vector3::Zero),
endPos(Vector3::Zero),
mRank(rank),
mRotateY(rotateY),
mScaleFloat(scale),
castleUpTimer(0.0f),
deadRagCount(0.0f),
isLook(true),
deadRagFlag(false)
{
	mScale = Vector3(30.0f, 30.0f, 30.0f)*scale;
	parameter.id = ACTOR_ID::CASTLE_ACTOR;
	parameter.isDead = false;
	parameter.radius = 17*scale;
	parameter.height = Vector3(0.0f, 34.0f, 0.0f)*scale;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(rotateY) *
		Matrix4::Translate(position);

	//城に乗っている敵の位置をセット
	Vector3 enemyScaleSet = Vector3(scale, scale, scale);
	CastleEnemyPosSet();
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon01, *this, -90 + rotateY,scale));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon02, *this, 0 + rotateY, scale));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon03, *this, 90 + rotateY, scale));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon04, *this, 180 + rotateY, scale));

	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor01, *this, -90, scale));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor02, *this, 180, scale));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor03, *this, 90, scale));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor04, *this, 0, scale));

	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear01, *this, -90 + rotateY,scale));
	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear02, *this, 0 + rotateY, scale));
	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear03, *this, 90 + rotateY, scale));
	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear04, *this, 180 + rotateY, scale));

	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f)
		, parameter.radius * 2, *this));

	//城出現時のパーティクルを生成
	world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, position, CastleAddSmokeNum, CastleAddSmokeSize, CastleAddSmokeSizePlusMin, CastleAddSmokeSizePlusMax));
	Sound::GetInstance().PlaySE(SE_ID::CONSTRUCTION_SE);

	startPos = position;
	endPos =  mPosition + Vector3(0.0f, parameter.radius * 2.0f, 0.0f);

	parent = &_parent;
}


Castle::~Castle()
{
	parent = nullptr;
	delete parent;
}

void Castle::Update()
{
	//マスターの状態取得
	MasterCastle* mas = static_cast<MasterCastle*>(const_cast<Actor*>(parent));
	//当たり判定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::AIR_GUN_ACTOR, COL_ID::CASTLE_AIRGUN_COL);
	prevPos = mPosition;

	//マスターが壊れたら自分も壊れる
	if (parent->GetParameter().isDead)
	{
		deadRagFlag = true;
	}
	if (deadRagFlag)
	{
		deadRagCount += Time::DeltaTime;
		//がれきを飛ばす
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::CHILD_CASTLE, breakSelect));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_BREAK_SE);
		if (deadRagCount >= 0.1f)
			parameter.isDead = true;
	}

	castleUpTimer += 15.0f* Time::DeltaTime;
	if (mas->castleRankUp())
	{
		startPos = mPosition;
		endPos = mPosition + Vector3(0.0f, parameter.radius * 2.0f, 0.0f);
		castleUpTimer = 0.0f;
	}

	mPosition = Vector3::Lerp(startPos, endPos, castleUpTimer);
	velocity = mPosition - prevPos;
	breakSelect = mas->getBreakSelect();

	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, parameter.mat);}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{
	//if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
	//{
	//	static_cast<MasterCastle*>(parent)->DamageTornad(mPosition);
	//}
	//if (colpara.colID == COL_ID::CASTLE_WIND_COL)
	//{
	//	static_cast<MasterCastle*>(parent)->DamageWind(mPosition);
	//}
	if (colpara.colID == COL_ID::CASTLE_AIRGUN_COL)
	{
		static_cast<MasterCastle*>(parent)->DamageAirGun(mPosition);
	}
}
void Castle::CastleEnemyPosSet()
{
	castleEnemyPos.cannon01 =
		(parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f )*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon02 =
		(parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f )*mScaleFloat+
		parameter.mat.GetPosition();

	castleEnemyPos.cannon03 =
		(parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon04 =
		(parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor01 =
		(parameter.mat.GetFront().Normalized()*15.0f +
		parameter.mat.GetLeft().Normalized()*-30.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor02 =
		(parameter.mat.GetFront().Normalized()*-27.0f +
		parameter.mat.GetLeft().Normalized()*-23.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor03 =
		(parameter.mat.GetFront().Normalized()*-14.0f +
		parameter.mat.GetLeft().Normalized()*30.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor04 =
		(parameter.mat.GetFront().Normalized()*27.0f +
		parameter.mat.GetLeft().Normalized()*22.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();


	castleEnemyPos.Spear01 =
		(parameter.mat.GetFront().Normalized()*22.0f +
		parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetUp().Normalized()*-15.0f)*mScaleFloat +
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius * 2, 0.0f);

	castleEnemyPos.Spear02 =
		(parameter.mat.GetFront().Normalized()*0.0f +
		parameter.mat.GetLeft().Normalized()*22.0f +
		parameter.mat.GetUp().Normalized()*-15.0f)*mScaleFloat +
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*2, 0.0f);

	castleEnemyPos.Spear03 =
		(parameter.mat.GetFront().Normalized()*-22.0f +
		parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetUp().Normalized()*-15.0f)*mScaleFloat +
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*2, 0.0f);

	castleEnemyPos.Spear04 =
		(parameter.mat.GetFront().Normalized()*0.0f +
		parameter.mat.GetLeft().Normalized()*-22.0f +
		parameter.mat.GetUp().Normalized()*-15.0f)*mScaleFloat +
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*2, 0.0f);

	castleEnemyPos.Soldier01 =
		(parameter.mat.GetFront().Normalized()*27.0f +
		parameter.mat.GetLeft().Normalized()*15.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier02 =
		(parameter.mat.GetFront().Normalized()*27.0f +
		parameter.mat.GetLeft().Normalized()*-15.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier03 =
		(parameter.mat.GetFront().Normalized()*-27.0f +
		parameter.mat.GetLeft().Normalized()*15.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier04 =
		(parameter.mat.GetFront().Normalized()*-27.0f +
		parameter.mat.GetLeft().Normalized()*-15.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier05 =
		(parameter.mat.GetFront().Normalized()*-13.0f +
		parameter.mat.GetLeft().Normalized()*-30.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier06 =
		(parameter.mat.GetFront().Normalized()*13.0f +
		parameter.mat.GetLeft().Normalized()*-30.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier07 =
		(parameter.mat.GetFront().Normalized()*-13.0f +
		parameter.mat.GetLeft().Normalized()*30.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier08 =
		(parameter.mat.GetFront().Normalized()*13.0f +
		parameter.mat.GetLeft().Normalized()*30.0f +
		parameter.mat.GetUp().Normalized()*5.0f)*mScaleFloat +
		parameter.mat.GetPosition();

}