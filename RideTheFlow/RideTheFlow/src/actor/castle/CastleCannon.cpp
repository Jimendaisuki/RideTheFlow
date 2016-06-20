#include "CastleCannon.h"

#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "CastleParameter.h"
#include "../../time/Time.h"
#include "../enemy/CannonBullet.h"
#include "../../math/Math.h"
#include "../Player.h"
#include  "../../Def.h"
#include "../../math/Quaternion.h"

CastleCannon::CastleCannon(IWorld& world, Vector3 position,Castle& _castle,float rotateY) :
Actor(world),
playerMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
playerDot(0),
mPosition(position),
mScale(2.0f),
angle(0.0f),
isLook(true)
{
	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;
	mRotateY = rotateY;
	castle = &_castle;

}
CastleCannon::~CastleCannon()
{

}
void CastleCannon::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	//プレイヤーの前
	Vector3 playerFront = playerMat.GetFront().Normalized()*CastleCameraFrontAttack + playerMat.GetPosition();
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
	if (castle->isLookPlayer())
	{
		mArrowNumber = CastleCannonNumber;
		mSecondAttack = CastleCannonSecondAttack;
	}
	else
	{
		mArrowNumber = CastleCannonNotLookAttack;
		mSecondAttack = CastleCannonNotLookSecondAttack;
	}
	isLook = true;
	//ダッシュ中以外はプレイヤーの前に矢を放つ
	if (tp.dashFlag)
	{
		playerDot = Vector3::Dot(parameter.mat.GetFront(), playerMat.GetPosition());
		attackAngleZ = playerAngle;
	}
	else
	{
		playerDot = Vector3::Dot(parameter.mat.GetFront(), playerFront*CastleCameraFrontAttack);
	}

	//城の大砲は旋回するよ
	if (Math::Abs(playerDot) >= 0.1f)
	{
		if (playerDot < 0 && angle < 90)
		{
			mRotateY += CastleCannonSwingSpeed*Time::DeltaTime;
			angle += CastleCannonSwingSpeed*Time::DeltaTime;
		}
		if (playerDot > 0 && angle > -90)
		{
			mRotateY -= CastleCannonSwingSpeed*Time::DeltaTime;
			angle -= CastleCannonSwingSpeed*Time::DeltaTime;
		}
		angle = Math::Clamp(angle, -90.0f, 90.0f);
	}


	//攻撃
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= CastleCannonAttackRange)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<CannonBullet>(world, mPosition+Vector3(0,10,0), *this, mRotateY - 90, attackAngleZ));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	//ベースの城が死んだら死ぬ
	if (castle->GetParameter().isDead)
	{
		parameter.isDead = true;
	}
	//城の速度を足す
	mPosition += castle->GetVelocity()*Time::DeltaTime;
	//マトリックス計算
	parameter.mat =
		Matrix4::Scale(mScale)*
	Quaternion::RotateAxis(Vector3::Up, mRotateY-90) *
	Matrix4::Translate(mPosition);
}
void CastleCannon::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CANNON_MODEL, parameter.mat);
	DrawLine3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), Vector3::ToVECTOR(parameter.mat.GetLeft().Normalized() * 100 + parameter.mat.GetPosition()), 255);
}
void CastleCannon::OnCollide(Actor& other, CollisionParameter colpara)
{
}