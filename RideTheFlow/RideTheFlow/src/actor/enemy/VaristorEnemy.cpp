#include "VaristorEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "VaristorBullet.h"
#include "../../math/Math.h"
#include "../Player.h"

VaristorEnemy::VaristorEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
cameraMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
mPosition(position),
toPoint(Vector3::Zero),
rotate(Vector3::Zero),
isLook(true)
{
	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;

}
VaristorEnemy::~VaristorEnemy()
{

}
void VaristorEnemy::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	world.EachActor(ACTOR_ID::CAMERA_ACTOR, [&](const Actor& other){
		cameraMat = other.GetParameter().mat;
	});
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);

	//敵とプレイヤーの角度を求める
	playerAngle = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		180 / 3.1415f;

	//プレイヤーが見えているかどうか
	if (isLook)
	{
		mArrowNumber = VaristorArrorwNum;
		mSecondAttack = VaristorAttackTime;
	}
	else
	{
		mArrowNumber = NotLookVaristorArrowNum;
		mSecondAttack = NotLookVaristorAttackTime;
	}
	isLook = true;

	//ダッシュ中以外はカメラの前に矢を放つ
	if (tp.dashFlag)
	{
		toPoint = playerMat.GetPosition();
	}
	else
	{
		toPoint = playerMat.GetFront().Normalized()*cameraFrontAttack + playerMat.GetPosition();
	}
	//攻撃
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= VaristorRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f&&
		playerAngle <= VaristorAttackMaxAngle&&playerAngle>=VaristorAttackMinAngle)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<VaristorBullet>(world, mPosition, toPoint, *this));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	parameter.mat = Matrix4::Translate(mPosition);
	Vector3 v = Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition()).Normalized();
	rotate.y = Math::Degree(Math::Atan2(v.x, v.z)) - 90.0f;
}
void VaristorEnemy::Draw() const
{
	//Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);
	DrawFormatString(0, 128, GetColor(0, 0, 0), "Yの値  %f", mPosition.y);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 1, GetColor(clor, clor, clor), 1, true);
	Model::GetInstance().Draw(MODEL_ID::BALLISTA_MODEL, parameter.mat.GetPosition(),rotate);
}
void VaristorEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
}