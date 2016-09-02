#include "ShipCannonEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "CannonBullet.h"
#include "../../math/Math.h"
#include "../Player.h"
#include "../../math/Quaternion.h"

ShipCannonEnemy::ShipCannonEnemy(IWorld& world, Vector3 position, ShipEnemy& se, bool left, float rotateY) :
Actor(world),
playerMat(Matrix4::Identity),
enemyMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
attackAngle(0),
playerDot(0),
backDot(0),
alpha(0.0f),
mPosition(position),
rotate(Vector3::Zero),
isLook(true),
mLeft(left)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Translate(position);
	parameter.radius = 10.0f;
	mSe = &se;
	rotate.y = rotateY;
}
ShipCannonEnemy::~ShipCannonEnemy()
{
	parent = nullptr;
	mSe = nullptr;
}
void ShipCannonEnemy::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	//あたり判定
	////world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_ENEMY_COL);
	//プレイヤーの前
	Vector3 playerFront = playerMat.GetFront().Normalized()*cameraFrontAttack + playerMat.GetPosition();
	//敵とプレイヤーの角度を求める
	float playerAngle = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		180 / 3.1415f;
	//敵が放つ攻撃の角度
	attackAngle = atan2(playerFront.y - mPosition.y,
		Math::Sqrt(Math::Pow(playerFront.z - mPosition.z, 2) +
		Math::Pow(playerFront.x - mPosition.x, 2))) *
		180 / 3.1415f;
	//プレイヤーの後ろにいるか
	Vector3 vec = (playerMat.GetPosition() - mSe->GetParameter().mat.GetPosition()).Normalized();
	backDot = Vector2::Dot(Vector2(mSe->GetParameter().mat.GetFront().x, mSe->GetParameter().mat.GetFront().z),
		Vector2(vec.x, vec.z));

	if (alpha <= 1.0f)
		alpha += Time::DeltaTime;

	//プレイヤーが見えているかどうか
	if (isLook)
	{
		mArrowNumber = ShipCannonShellNum;
		mSecondAttack = ShipCannonAttackTime;
	}
	else
	{
		mArrowNumber = ShipNotLookCannonShellNum;
		mSecondAttack = ShipNotLookCannonAttackTime;
	}
	isLook = true;
	//ダッシュ中以外はプレイヤーの前に矢を放つ
	if (tp.dashFlag)
	{

		Vector3 vec = (playerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
		playerDot = Vector2::Dot(Vector2(-parameter.mat.GetFront().x, -parameter.mat.GetFront().z),
			Vector2(vec.x, vec.z));
		attackAngle = playerAngle;
	}
	else
	{
		Vector3 vec = (playerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
		playerDot = Vector2::Dot(Vector2(-parameter.mat.GetFront().x, -parameter.mat.GetFront().z),
			Vector2(vec.x, vec.z));
	}

	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (backDot >= 0 && mLeft)
	{
		Attack();
		if (Math::Abs(playerDot) >= 0.1f)
		{
			if (playerDot > 0)
			{
				rotate.y += VaristorSwingSpeed*Time::DeltaTime;
			}
			else
			{
				rotate.y -= VaristorSwingSpeed*Time::DeltaTime;
			}
		}
	}
	if (backDot < 0 && !mLeft)
	{
		Attack();
		if (Math::Abs(playerDot) >= 0.1f)
		{
			if (playerDot > 0)
			{
				rotate.y += VaristorSwingSpeed*Time::DeltaTime;
			}
			else
			{
				rotate.y -= VaristorSwingSpeed*Time::DeltaTime;
			}
		}
	}

	if (mSe->GetParameter().isDead)
	{
		parameter.isDead = true;
	}

	if (mLeft)
		mPosition = mSe->GetShipEnemyPos().cannonPosLeft;
	else
		mPosition = mSe->GetShipEnemyPos().cannonPosRight;

	//マトリックス計算
	parameter.mat =
		Quaternion::RotateAxis(Vector3::Up, rotate.y) *
		Matrix4::Scale(1.0f)*
		Matrix4::Translate(mPosition);
	enemyMat =
		Quaternion::RotateAxis(Vector3::Up, rotate.y - 90) *
		Matrix4::Scale(1.0f)*
		Matrix4::Translate(mPosition + parameter.mat.GetLeft().Normalized()*-3.0f);
}
void ShipCannonEnemy::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CANNON_MODEL, parameter.mat,alpha);
	Model::GetInstance().Draw(MODEL_ID::HUMAN_CANNON_MODEL, enemyMat,alpha);
}
void ShipCannonEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::TORNADO_ENEMY_COL)
	{
		parameter.isDead = true;
	}
}
void ShipCannonEnemy::Attack()
{
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= ShipCannonRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f&&
		playerAngle <= ShipCannonAttackMaxAngle&&playerAngle >= ShipCannonAttackMinAngle)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<CannonBullet>(world, mPosition, *this, rotate.y - 90, attackAngle,ShipCannonInitialVelocity,ShipCannonBulletAccuracy));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
}