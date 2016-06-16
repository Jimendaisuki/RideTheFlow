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


Castle::Castle(IWorld& world, Vector3 position, Actor& _parent) :
Actor(world),
arrowCount(0),
attackRag(0.0f),
playerMat(Matrix4::Identity),
mPosition(position),
mScale(30, 30, 30),
mAttackTime(0.0f),
castleDown(true),
isLook(false),
InvincibleTimer(0.0f),
damage(true)
{
	parameter.HP = BaseCastleHp;
	parameter.isDead = false;
	parameter.radius = 17;
	parameter.height = Vector3(0.0f,34.0f,0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	parent =&_parent;
	//城に乗っている敵の位置をセット
	CastleEnemyPosSet();
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon01, *this, -90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon02, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon03, *this, 90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon04, *this, 180));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear01, *this, -90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear02, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear03, *this, 90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear04, *this, 180));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier01, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier02, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier03, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier04, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier05, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier06, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier07, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<SoldierEnemy>(world, castleEnemyPos.Soldier08, *this, 0));
}


Castle::~Castle()
{

}

void Castle::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	//当たり判定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::CASTLE_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
	//城に当たったらストップ
	if (castleDown)
	{
		velocity.y -= 400.0f*Time::DeltaTime;
		if (velocity.y <= -400.0f)
			velocity.y = -400.0f;
	}
	else
	{
		velocity = 0;
	}
	castleDown = true;
	mPosition += velocity*Time::DeltaTime;

	//マスターが壊れたら自分も壊れる
	if (parent->GetParameter().isDead)
	{
		parameter.isDead = true;
		//がれきを飛ばす
		for (int i = 0; i < 8; i++){
			world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleBlock>(world, mPosition + Vector3(0.0f, Random::GetInstance().Range(-10.0f, 10.0f), 0.0f)));
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

	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::Translate(mPosition);
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, parameter.mat);
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

	if (colpara.colID == COL_ID::CASTLE_CASTLE_COL&&colpara.colFlag)
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