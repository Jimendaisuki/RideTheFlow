#include "MasterCastle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../EnemyBullet.h"
#include "castle.h"
#include "../../game/Random.h"
#include "CastleParameter.h"

MasterCastle::MasterCastle(IWorld& world, Vector3 position) :
Actor(world),
attackTime(0),
castleTime(0),
attackRag(0),
arrowCount(0),
mRank(Rank),
mPosition(position),
playerMat(Matrix4::Identity),
mScale(30,30,30)
{
	
    Vector2 side = Vector2(mScale.x, mScale.z) / 2;
    parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
	parameter.isDead = false;
	parameter.height = Vector3(0.0f,CastleHeight,0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	
	//startPos = Matrix4::GetPosition(parameter.mat);
	//endPos = Matrix4::GetPosition(parameter.mat) + parameter.height * Vector3::Up;
}

MasterCastle::~MasterCastle()
{
	
}

void MasterCastle::Update()
{

	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

	attackTime += Time::DeltaTime;
	castleTime += Time::DeltaTime;
	attackRag += Time::DeltaTime;
	if (castleTime >= RankUpSecond&&mRank>0)
	{
		mRank--;
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world,
			Vector3(mPosition.x, mPosition.y + (CastleHeight*(Rank - mRank)), mPosition.z)));
		castleTime = 0.0f;
	}

	if (attackTime >= SecondAttack&&attackRag >= 0.03f&&arrowCount < ArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= AttackRange&&
		abs(playerMat.GetPosition().y-mPosition.y)>=2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition));
    if (arrowCount >= ArrowNumber)
		{
			arrowCount = 0;
			attackTime = 0.0f;
		}
	}
}

void MasterCastle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
	//DrawCapsule3D(startPos, endPos, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	//DrawLine3D(startPos, endPos, GetColor(255, 0, 0));

	//DrawCube3D(
	//	Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) / 2, 
	//	Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) / 2, 
	//	color, 
	//	GetColor(0, 0, 0), 
	//	false);
	//DrawFormatString(10, 100, GetColor(255, 255, 255), "CastlePos	: %f %f %f", Matrix4::GetPosition(parameter.mat).x, Matrix4::GetPosition(parameter.mat).y, Matrix4::GetPosition(parameter.mat).z);
	//DrawFormatString(10, 120, GetColor(255, 255, 255), "CastleScale	: %f %f %f", Matrix4::GetScale(parameter.mat).x, Matrix4::GetScale(parameter.mat).y, Matrix4::GetScale(parameter.mat).z);
	//if (isHit)
	//{
	//	DrawFormatString(10, 400, GetColor(255, 255, 255), "Hit");
	//}
}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}