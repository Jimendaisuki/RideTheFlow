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
arrowCount(0),
attackRag(0.0f),
playerMat(Matrix4::Identity),
velocity(Vector3::Zero),
mPosition(position),
mAttackTime(0.0f),
castleDown(true),
isLook(true),
InvincibleTimer(0.0f),
damage(true),
startPos(Vector3::Zero),
endPos(Vector3::Zero),
castleUpTimer(0.0f)
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
	test = parameter.mat.GetFront().Normalized() * 100 + parameter.mat.GetPosition();
	parent = &_parent;
	//城に乗っている敵の位置をセット
	Vector3 enemyScaleSet = Vector3(scale, scale, scale);
	mScaleFloat = scale;
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

	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier01, *this, 180 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier02, *this, 180 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier03, *this, 0 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier04, *this, 0 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier05, *this, 90 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier06, *this, 90 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier07, *this, -90 + rotateY, scale));
	//world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier08, *this, -90 + rotateY, scale));
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f)
		, parameter.radius * 2, *this));
	//城出現時のパーティクルを生成
	world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, position, CastleAddSmokeNum, CastleAddSmokeSize, CastleAddSmokeSizePlusMin, CastleAddSmokeSizePlusMax));
	Sound::GetInstance().PlaySE(SE_ID::CONSTRUCTION_SE);

	mRank = rank;
	mRotateY = rotateY;

	sevePos = mPosition;
	prevPos = mPosition;
	startPos = mPosition;
	endPos = endPos = mPosition + Vector3(0.0f, parameter.radius * 2.0f, 0.0f);
}


Castle::~Castle()
{

}

void Castle::Update()
{
	//マスターの状態取得
	MasterCastle* mas = static_cast<MasterCastle*>(const_cast<Actor*>(parent));
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	//当たり判定
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::MASTER_CASTLE_ACTOR, COL_ID::MASTERCASTLE_CASTLE_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::CASTLE_CASTLE_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::AIR_GUN_ACTOR, COL_ID::CASTLE_AIRGUN_COL);
	prevPos = mPosition;

	//マスターが壊れたら自分も壊れる
	if (mas->RagDead())
	{
		parameter.isDead = true;
		//がれきを飛ばす
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::CHILD_CASTLE, breakSelect));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_BREAK_SE);
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

	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
	isLook = true;
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, parameter.mat);
	//DrawFormatString(0, 464, GetColor(0, 0, 0), "positionx   %f,%f,%f", parameter.mat.GetPosition().x, parameter.mat.GetPosition().y, parameter.mat.GetPosition().z);
	////DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetFront().Normalized() * -100 + parameter.mat.GetPosition()), 20, 10, 1, 1, TRUE);
	////DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetLeft().Normalized() * 100 + parameter.mat.GetPosition()), 20, 10, 1, 1, TRUE);
	////DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetLeft().Normalized() * -100 + parameter.mat.GetPosition()), 20, 10, 1, 1, TRUE);
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{

	//全部見えてなかったら
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL&&damage)
	{
		parameter.HP -= CastleDamegeTornado;
		//ダメージを喰らった時のパーティクル
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, Vector3::Zero, DamageSmokeNum, DamageSmokeSize, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		//ダメージ食らった時の音
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::MASTER_CASTLE, BREAK_SELECT::DAMAGE));
		damage = false;
	}
	if (colpara.colID == COL_ID::CASTLE_WIND_COL&&damage)
	{
		parameter.HP -= CastleDamegeWind;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, Vector3::Zero, DamageSmokeNum, DamageSmokeSize, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::MASTER_CASTLE, BREAK_SELECT::DAMAGE));
		damage = false;
	}
	if (colpara.colID == COL_ID::CASTLE_AIRGUN_COL&&damage)
	{
		parameter.HP -= CastleDamageWindBall;
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, Vector3::Zero, DamageSmokeNum, DamageSmokeSize, DamageSmokeSizePlusMin, DamageSmokeSizePlusMax));
		Sound::GetInstance().PlaySE(SE_ID::CASTLE_HIT_SE);
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::MASTER_CASTLE, BREAK_SELECT::DAMAGE));
		damage = false;
	}

	if (colpara.colID == COL_ID::CASTLE_CASTLE_COL&&colpara.colFlag)
	{
		castleDown = false;
	}
	if (colpara.colID == COL_ID::MASTERCASTLE_CASTLE_COL&&colpara.colFlag)
	{
		castleDown = false;
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