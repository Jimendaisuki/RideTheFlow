#include "ArmyEnemy.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
#include "EnemyParameter.h"
#include "../../time/Time.h"
#include "EnemyBullet.h"
#include "../../math/Math.h"

ArmyEnemy::ArmyEnemy(IWorld& world, Vector3 position) :
Actor(world),
playerMat(Matrix4::Identity),
cameraMat(Matrix4::Identity),
attackRag(0),
attackTime(0),
arrowCount(0),
playerAngle(0),
mPosition(position),
isLook(true)
{
	parameter.isDead = false;
	parameter.mat = Matrix4::Translate(mPosition);
	parameter.radius = 10.0f;
	
}
ArmyEnemy::~ArmyEnemy()
{

}
void ArmyEnemy::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	world.EachActor(ACTOR_ID::CAMERA_ACTOR, [&](const Actor& other){
		cameraMat = other.GetParameter().mat;
	});
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);

	//“G‚ÆƒvƒŒƒCƒ„[‚ÌŠp“x‚ð‹‚ß‚é
	playerAngle = atan2(playerMat.GetPosition().y - mPosition.y,
		Math::Sqrt(Math::Pow(playerMat.GetPosition().z - mPosition.z, 2) +
		           Math::Pow(playerMat.GetPosition().x - mPosition.x, 2))) *
		           180 / 3.1415f;

	//ƒvƒŒƒCƒ„[‚ªŒ©‚¦‚Ä‚¢‚é‚©‚Ç‚¤‚©
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
	isLook = true;

	//UŒ‚
	attackRag += Time::DeltaTime;
	attackTime += Time::DeltaTime;
	if (attackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= ArmyRange &&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, playerMat.GetPosition()));
		if (arrowCount >= mArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
	

	if (playerAngle <= ArmyNear)
	{
		//ˆÚ“®
		mPosition += Vector3::Direction(mPosition, playerMat.GetPosition()).Normalized()*
			Vector3(1, 0, 1)*ArmySpeed*Time::DeltaTime;
	}
	parameter.mat = Matrix4::Translate(mPosition);
}
void ArmyEnemy::Draw() const
{
	//Model::GetInstance().Draw(MODEL_ID::ARROW_MODEL, parameter.mat);
	DrawFormatString(0, 128, GetColor(0, 0, 0), "‚È‚·Šp xy  %f", playerAngle);
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 1, GetColor(255, 255, 255), 1, true);
}
void ArmyEnemy::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
}