#include "CannonEnemy.h"
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

CannonEnemy::CannonEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
playerDot(0),
mPosition(position),
isLook(true)
{
	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;
}
CannonEnemy::~CannonEnemy()
{

}
void CannonEnemy::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	//あたり判定
	////world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ENEMY_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::BULLET_WIND_COL);
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

	//プレイヤーが見えているかどうか
	if (isLook)
	{
		mArrowNumber = CannonShellNum;
		mSecondAttack = CannonAttackTime;
	}
	else
	{
		mArrowNumber = NotLookCannonShellNum;
		mSecondAttack = NotLookCannonAttackTime;
	}
	isLook = true;

	//ダッシュ中以外はプレイヤーの前に矢を放つ
	if (tp.dashFlag)
	{
		playerDot = Vector3::Dot(parameter.mat.GetLeft(), playerMat.GetPosition());
		attackAngleZ = playerAngle;
	}
	else
	{
		playerDot = Vector3::Dot(parameter.mat.GetLeft(), playerFront*cameraFrontAttack);
	}

	//右にいるか左にいるかを確かめ旋回する
	if (Math::Abs(playerDot) >= 2.0f)
	{
    	if (playerDot > 0)
		{
			rotate.y += ConnonSwingSpeed*Time::GetInstance().deltaTime();
		}
		else
		{
			rotate.y -= ConnonSwingSpeed*Time::GetInstance().deltaTime();
		}
	}


	//攻撃
	attackRag += Time::GetInstance().deltaTime();
	attackTime += Time::GetInstance().deltaTime();
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= CannonRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f&&
		playerAngle <= CannonAttackMaxAngle&&playerAngle >= CannonAttackMinAngle)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<CannonBullet>(world, mPosition, *this,rotate.y-90,attackAngleZ,CannonInitialVelocity,CannonShellAccuracy));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	//マトリックス計算
	parameter.mat =
		Quaternion::RotateAxis(Vector3::Up,rotate.y) *
		Matrix4::Translate(mPosition);

}
void CannonEnemy::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CANNON_MODEL, parameter.mat);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), 5, 20, 1, 1, FALSE);
}
void CannonEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::TORNADO_ENEMY_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::ENEMY_WIND_COL)
	{

	}
}