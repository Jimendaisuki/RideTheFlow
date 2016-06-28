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

Castle::Castle(IWorld& world, Vector3 position, Actor& _parent, int rank, float rotateY) :
Actor(world),
arrowCount(0),
attackRag(0.0f),
playerMat(Matrix4::Identity),
velocity(Vector3::Zero),
mPosition(position),
mScale(30.0f),
mAttackTime(0.0f),
castleDown(true),
isLook(false),
InvincibleTimer(0.0f),
damage(true),
startPos(Vector3::Zero),
endPos(Vector3::Zero),
castleUpTimer(0.0f)
{
	parameter.id = ACTOR_ID::CASTLE_ACTOR;
	parameter.isDead = false;
	parameter.radius = 17;
	parameter.height = Vector3(0.0f, 34.0f, 0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(rotateY) *
		Matrix4::Translate(position);
	test = parameter.mat.GetFront().Normalized() * 100 + parameter.mat.GetPosition();
	parent = &_parent;
	//城に乗っている敵の位置をセット
	CastleEnemyPosSet();
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon01, *this, -90 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon02, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon03, *this, 90 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon04, *this, 180 + rotateY));

	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor01, *this, -90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor02, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor03, *this, 90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleVaristor>(world, castleEnemyPos.varistor04, *this, 180));


	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear01, *this, -90 + rotateY));
	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear02, *this, 0 + rotateY));
	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear03, *this, 90 + rotateY));
	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear04, *this, 180 + rotateY));

	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier01, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier02, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier03, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier04, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier05, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier06, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier07, *this, 0 + rotateY));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier08, *this, 0 + rotateY));
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius, 0.0f)
		, parameter.radius * 2, *this));
	//城出現時のパーティクルを生成
	world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, position));
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
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::AIR_GUN_ACTOR, COL_ID::CASTLE_AIRGUN_COL);
	prevPos = mPosition;

	//マスターが壊れたら自分も壊れる
	if (mas->RagDead())
	{
		parameter.isDead = true;
		//がれきを飛ばす
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::MASTER_CASTLE, breakSelect));
	}

	castleUpTimer += 20.0f* Time::DeltaTime;
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
}

void Castle::Draw() const
{

	Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, parameter.mat);
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()+Vector3(0.0f,parameter.radius,0.0f)), parameter.radius, 10, 1, 1, TRUE);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetFront().Normalized() * -100 + parameter.mat.GetPosition()), 20, 10, 1, 1, TRUE);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetLeft().Normalized() * 100 + parameter.mat.GetPosition()), 20, 10, 1, 1, TRUE);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetLeft().Normalized() * -100 + parameter.mat.GetPosition()), 20, 10, 1, 1, TRUE);
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
		damage = false;
	}
	if (colpara.colID == COL_ID::CASTLE_WIND_COL&&damage)
	{
		parameter.HP -= CastleDamegeWind;
		damage = false;
	}
	if (colpara.colID == COL_ID::CASTLE_AIRGUN_COL&&damage)
	{
		parameter.HP -= CastleDamageWindBall;
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
		parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon02 =
		parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon03 =
		parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon04 =
		parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor01 =
		parameter.mat.GetFront().Normalized()*15.0f +
		parameter.mat.GetLeft().Normalized()*-30.0f +
		parameter.mat.GetUp().Normalized()*6.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor02 =
		parameter.mat.GetFront().Normalized()*28.0f +
		parameter.mat.GetLeft().Normalized()*15.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor03 =
		parameter.mat.GetFront().Normalized()*-15.0f +
		parameter.mat.GetLeft().Normalized()*30.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.varistor04 =
		parameter.mat.GetFront().Normalized()*-28.0f +
		parameter.mat.GetLeft().Normalized()*-15.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();


	castleEnemyPos.Spear01 =
		parameter.mat.GetFront().Normalized()*22.0f +
		parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear02 =
		parameter.mat.GetFront().Normalized()*0.0f +
		parameter.mat.GetLeft().Normalized()*22.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear03 =
		parameter.mat.GetFront().Normalized()*-22.0f +
		parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear04 =
		parameter.mat.GetFront().Normalized()*0.0f +
		parameter.mat.GetLeft().Normalized()*-22.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier01 =
		parameter.mat.GetFront().Normalized()*10.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier02 =
		parameter.mat.GetFront().Normalized()*-10.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier03 =
		parameter.mat.GetFront().Normalized()*10.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier04 =
		parameter.mat.GetFront().Normalized()*-10.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier05 =
		parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*-10.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier06 =
		parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*10.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier07 =
		parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*-10.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Soldier08 =
		parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*10.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

}