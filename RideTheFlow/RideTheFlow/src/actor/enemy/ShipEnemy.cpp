#include "ShipEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "../enemy/CannonBullet.h"
#include "../../math/Math.h"
#include "../Player.h"
#include  "../../Def.h"
#include "../../math/Quaternion.h"
#include "DoragonSpearEnemy.h"
#include "ShipVaristorEnemy.h"
#include "ShipCannonEnemy.h"
#include "../castle/CastleCannon.h"
#include "../island/FloatingIsland.h"
ShipEnemy::ShipEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
isLandPos(Vector3::Zero),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
shipAngle(0),
isLandDot(0),
shipLow(1.0f),
mPosition(position),
invincibleTimer(0.0f),
isLook(true),
isLandCol(false)
{
	parameter.id = ACTOR_ID::SHIP_ENEMY_ACTOR;
	parameter.HP = ShipHp;
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(1.0f) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	parameter.radius = 40.0f;
	playerDot = 0.0f;

	ShipEnemyPosition();

	world.Add(ACTOR_ID::DORAGONSPEAR_ACTOR, std::make_shared<DoragonSpearEnemy>(world, shipEnemyPos.spearPos,*this,*this));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipVaristorEnemy>(world, shipEnemyPos.varistorPosLeft,*this,true,-90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipVaristorEnemy>(world, shipEnemyPos.varistorPosRight, *this, false, 90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipCannonEnemy>(world, shipEnemyPos.cannonPosLeft, *this, true, -90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipCannonEnemy>(world, shipEnemyPos.cannonPosRight, *this, false, 90));
}
ShipEnemy::~ShipEnemy()
{

}
void ShipEnemy::Update()
{
	TackleParameter tp;
	Matrix4 fiMat;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});

	//あたり判定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ENEMY_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_SHIPENEMY_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::ENEMY_WIND_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::NO_SHIP_AREA_ACTOR, COL_ID::SHIP_ISLAND_COL);
	ShipEnemyPosition();

	//プレイヤーの前
	Vector3 playerFront = playerMat.GetFront().Normalized()*cameraFrontAttack + playerMat.GetPosition();
	//敵とプレイヤーの角度を求める
	float playerAngle = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		180 / 3.1415f;
	//敵が放つ攻撃の角度
	float attackAngleZ = atan2(playerFront.y - mPosition.y,
		Math::Sqrt(Math::Pow(playerFront.z - mPosition.z, 2) +
		Math::Pow(playerFront.x - mPosition.x, 2))) *
		180 / 3.1415f;


	Vector3 vec = (playerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
	playerDot = Vector2::Dot(Vector2(parameter.mat.GetFront().x, parameter.mat.GetFront().z), Vector2(vec.x, vec.z));
	//プレイヤーの方向に向く
	if (!isLandCol)
	{
		if (Math::Abs(playerDot) >= 0.1f)
		{
			if (playerDot >= 0)
			{
				shipAngle -= ShipSwingSpeed*Time::DeltaTime;
			}
			else
			{
				shipAngle += ShipSwingSpeed*Time::DeltaTime;
			}
		}
	}
	
	mPosition += parameter.mat.GetLeft().Normalized()*ShipSpeed / shipLow*Time::DeltaTime;
	if (!isLandCol)
		mPosition += Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition())*
		Vector3(0.0f, ShipUpDownSpeed, 0.0f)*Time::DeltaTime;

	//浮島を迂回する
	if (isLandCol)
	{
		Vector3 vec = (isLandPos - parameter.mat.GetPosition()).Normalized();
		isLandDot = Vector2::Dot(Vector2(parameter.mat.GetFront().x, parameter.mat.GetFront().z), Vector2(vec.x, vec.z));

		shipLow = 0.5f;
		if (isLandDot <= 0)
		{
			shipAngle -= 50.0f*Time::DeltaTime;
		}
		else
		{
			shipAngle += 50.0f*Time::DeltaTime;
		}
		mPosition += Vector3::Direction(isLandPos, parameter.mat.GetPosition()).Normalized()*Vector3(1,0,1);
	}
	else
	{
		shipLow = 1.0f;
	}
	isLandCol = false;
	//無敵時間
	if (!damege)
	{
		invincibleTimer += Time::DeltaTime;
		if (invincibleTimer >= ShipInvincibleTime)
		{
			damege = true;
			invincibleTimer = 0.0f;
		}
	}
	//HPが0になったら死ぬ
	if (parameter.HP <= 0)
		parameter.isDead = true;
	
	//マトリックス計算
	parameter.mat =
		Quaternion::RotateAxis(Vector3::Up,shipAngle)*
		Matrix4::Translate(mPosition);

}
void ShipEnemy::Draw() const
{
	//モデルの方向が違う
	Model::GetInstance().Draw(MODEL_ID::SHIP_MODEL, parameter.mat);
	DrawFormatString(0, 432, GetColor(0, 0, 0), "ShipHp   %f", parameter.HP);


}
void ShipEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::PLAYER_SHIPENEMY_COL)
	{
		mPosition += Vector3::Direction(colpara.colPos, parameter.mat.GetPosition() + parameter.mat.GetPosition() + parameter.mat.GetUp().Normalized()*25.0f)*100*Time::DeltaTime;
	}
	if (colpara.colID == COL_ID::SHIP_ISLAND_COL)
	{
		isLandCol = true;
		isLandPos = colpara.colPos;
	}

	//ダメージ関係
	if (colpara.colID == COL_ID::TORNADO_ENEMY_COL&&damege)
	{
		parameter.HP -= ShipDamegeTornado;
		damege = false;
	}
	if (colpara.colID == COL_ID::ENEMY_WIND_COL)
	{
		mPosition += colpara.colVelosity;
		if (damege)
		{
			parameter.HP -= ShipDamegeWind;
			damege = false;
		}
	}
}

void ShipEnemy::ShipEnemyPosition()
{
	shipEnemyPos.spearPos = parameter.mat.GetLeft().Normalized()*40.0f +
		parameter.mat.GetPosition() + parameter.mat.GetUp().Normalized()*5.0f;

	shipEnemyPos.varistorPosLeft = parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetFront().Normalized()*5.0f +
		parameter.mat.GetUp().Normalized()*20.0f +
		parameter.mat.GetPosition();

	shipEnemyPos.varistorPosRight = parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetFront().Normalized()*-5.0f +
		parameter.mat.GetUp().Normalized()*20.0f +
		parameter.mat.GetPosition();

	shipEnemyPos.cannonPosLeft = parameter.mat.GetLeft().Normalized()*27.0f +
		parameter.mat.GetFront().Normalized()*7.0f +
		parameter.mat.GetUp().Normalized()*10.0f +
		parameter.mat.GetPosition();

	shipEnemyPos.cannonPosRight = parameter.mat.GetLeft().Normalized()*27.0f +
		parameter.mat.GetFront().Normalized()*-7.0f +
		parameter.mat.GetUp().Normalized()*10.0f +
		parameter.mat.GetPosition();
}
