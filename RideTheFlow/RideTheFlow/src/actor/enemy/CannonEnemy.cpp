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

CannonEnemy::CannonEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
cameraMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
mPosition(position),
isLook(true),
toPoint(Vector3::Zero)
{
	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;
	Vector3 v = Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition()).Normalized();
	rotate = Vector3(0.0f, Math::Degree(Math::Atan2(v.x, v.z)) - 90.0f, 0.0f);
	restRotate = rotate;
	rotateVelocity = Vector3::Zero;
	test = 0.0f;
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
		mArrowNumber = CannonShellNum;
		mSecondAttack = CannonAttackTime;
	}
	else
	{
		mArrowNumber = NotLookCannonShellNum;
		mSecondAttack = NotLookCannonAttackTime;
	}
	//ダッシュ中以外はカメラの前に矢を放つ
	if (tp.dashFlag)
	{
		toPoint = playerMat.GetPosition();
	}
	else
	{
		toPoint = playerMat.GetFront().Normalized()*cameraFrontAttack+playerMat.GetPosition();
	}

	isLook = true;


	Vector3 v = (playerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
	restRotate.y = Math::Degree(Math::Atan2(v.x, v.z)) - 90.0f;

	Vector3 stretch = (rotate - restRotate);
	Vector3 force = -ConnonSwingSpeed * stretch;
	Vector3 acceleration = force / 2.0f;
	rotateVelocity = 0.5f * (rotateVelocity + acceleration);
	rotate += rotateVelocity;

	float rotateZ = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		180 / 3.1415f;

	//攻撃
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= CannonRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f&&
		playerAngle <= CannonAttackMaxAngle&&playerAngle >= CannonAttackMinAngle)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<CannonBullet>(world, mPosition, *this,rotate.y,rotateZ));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	parameter.mat = Matrix4::Translate(mPosition);

}
void CannonEnemy::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CANNON_MODEL, parameter.mat.GetPosition(),rotate);
	//DrawFormatString(0, 256, GetColor(0, 0, 0), "rotateY   %f", rotateZ);
}
void CannonEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
}