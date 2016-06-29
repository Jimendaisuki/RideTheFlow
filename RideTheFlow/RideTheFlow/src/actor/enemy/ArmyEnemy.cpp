#include "ArmyEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "EnemyBullet.h"
#include "../../math/Math.h"
#include "../../UIactor/EnemyPoint.h"
#include "../../sound/Sound.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"

ArmyEnemy::ArmyEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
mPosition(position),
toPoint(Vector3::Zero),
rotate(Vector3::Zero),
isLook(true),
downTime(0.0f)
{
	parameter.id = ACTOR_ID::ARMY_ENEMY_ACTOR;
	parameter.HP = 1.0f;
	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;
	player = static_cast<Player*>(world.GetPlayer().get());
	world.UIAdd(UI_ID::ENEMY_POINT_UI, std::make_shared<EnemyPoint>(world, *this));
}
ArmyEnemy::~ArmyEnemy()
{
	
}
void ArmyEnemy::Update()
{
	TackleParameter tp;
	tp = player->ReturnTackleParameter();
	playerMat = player->GetParameter().mat;
	 
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::STAGE_ACTOR, COL_ID::ARMYENEMY_STAGE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ENEMY_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::ENEMY_WIND_COL);

	//敵とプレイヤーの角度を求める
	playerAngle = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		           Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		           180 / 3.1415f;

	//プレイヤーが見えているかどうか
	if (isLook)
	{
		mArrowNumber = ArmyArrorwNum;
		mSecondAttack = ArmyAttackTime;
	}
	else
	{
		mArrowNumber = NotLookArmyArrorwNum;
		mSecondAttack = NotLookArmyAttackTime;
	}

	//ダッシュ中以外はカメラの前に矢を放つ
	if (tp.dashFlag)
	{
		toPoint = playerMat.GetPosition();
	}
	else
	{
		toPoint = playerMat.GetFront().Normalized()*cameraFrontAttack + playerMat.GetPosition();
	}

	isLook = true;

	//攻撃
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;

	//if (attackTime >= mSecondAttack&&attackRag >= 0.3f&&arrowCount < mArrowNumber&&
	//	Vector3::Distance(playerMat.GetPosition(), mPosition) <= ArmyRange &&
	//	abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f)
	//{
	//	attackRag = 0.0f;
	//	arrowCount++;
	//	world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, toPoint, *this));
	//	if (arrowCount >= mArrowNumber)
	//	{
	//		arrowCount = 0;
	//		attackTime = 0.0f;
	//	}
	//}


	if (attackTime >= mSecondAttack&&attackRag >= 0.0f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= ArmyRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, toPoint,*this));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	if (playerAngle <= ArmyNear)
	{
		//移動
		mPosition += Vector3::Direction(mPosition, player->GetParameter().mat.GetPosition()).Normalized()*
			Vector3(1, 0, 1)*ArmySpeed*Time::DeltaTime;
	}
	downTime += Time::DeltaTime;
	if (downTime >= 2.0f)
	{
		mPosition.y -= 5.0f*Time::DeltaTime;
		downTime = 3.0f;
	}
	parameter.mat = Matrix4::Translate(mPosition);
	Vector3 v = Vector3::Direction(parameter.mat.GetPosition(), player->GetParameter().mat.GetPosition()).Normalized();
	rotate.y = Math::Degree(Math::Atan2(v.x, v.z)) - 90.0f;
}
void ArmyEnemy::Draw() const
{
	for (int i = 0; i < 3;i++)
	for (int j = 0; j < 3; j++)
	{
		Matrix4 m;
		m = Matrix4::RotateY(rotate.y-90) * Matrix4::Translate(mPosition + Vector3(10 * i, 0, 10 * j));
		Model::GetInstance().Draw(MODEL_ID::HUMAN_BALLISTA_MODEL, m);
	}
}
void ArmyEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::ARMYENEMY_STAGE_COL)
	{
		mPosition = colpara.colPos;
	}
	if (colpara.colID == COL_ID::TORNADO_ENEMY_COL)
	{
		parameter.isDead = true;
		auto se = (SE_ID)Random::GetInstance().Range(SE_ID::SCREAM_1_SE, SE_ID::SCREAM_5_SE);
		Sound::GetInstance().PlaySE(se);
	}
	if (colpara.colID == COL_ID::ENEMY_WIND_COL)
	{
		//仕様確認
		parameter.isDead = true;
		auto se = (SE_ID)Random::GetInstance().Range(SE_ID::SCREAM_1_SE, SE_ID::SCREAM_5_SE);
		Sound::GetInstance().PlaySE(se);
	}
}