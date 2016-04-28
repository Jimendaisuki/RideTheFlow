#include "MasterCastle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../EnemyBullet.h"
#include "../EnemyGunBullet.h"
#include "../EnemyVaristorBullet.h"
#include "../ParachuteBombBullet.h"
#include "castle.h"
#include "../../game/Random.h"

//é‚Ìã‚ÉÏ‚Ýd‚È‚éé‚Ì’i”
const int Rank = 0;
//é‚ªÏ‚Ý‚ ‚ª‚éŽžŠÔ(•b)
const float RankUpSecond = 5.0f;
//é‚ªUŒ‚‚µ‚Ä‚­‚é”ÍˆÍ
const float AttackRange = 200.0f;
//é‚ÌUŒ‚ƒN[ƒ‹ƒ^ƒCƒ€(•b)
const float SecondAttack = 5.0f;
//é‚ªˆê‰ñ‚Éo‚·–î‚Ì–{”(–{)
const int ArrowNumber = 2;
//UŒ‚‚Ì¸“x(”’l‚ª¬‚³‚¢‚Ù‚Ç‚¸“x)
const float ArrowAccuracy = 20.0f;

//éƒ‚ƒfƒ‹‚Ì‚‚³‚Ì‚R”{(ƒXƒP[ƒ‹˜M‚Á‚Ä‚é‚©‚ç)
const float CastleHeight = 30.0f;

MasterCastle::MasterCastle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world),
attackTime(0),
castleTime(0),
attackRag(0),
arrowCount(0),
mRank(Rank),
mPosition(position),
startPos(Vector3::Zero),
endPos(Vector3::Zero),
playerMat(Matrix4::Identity),
randomTarget(0)
{
    Vector2 side = Vector2(scale.x, scale.z) / 2;
    parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
	parameter.isDead = false;
	parameter.height = CastleHeight;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);
	
	startPos = Matrix4::GetPosition(parameter.mat);
	endPos = Matrix4::GetPosition(parameter.mat) + parameter.height * Vector3::Up;
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
			Vector3(mPosition.x, mPosition.y + (CastleHeight*(Rank - mRank)), mPosition.z),
			Vector3(0, 0, 0), Vector3(30), 
			SecondAttack, AttackRange,ArrowNumber,ArrowAccuracy,attackTime));
		castleTime = 0.0f;
	}

	if (attackTime >= SecondAttack&&attackRag >= 0.03f&&arrowCount < ArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= AttackRange&&
		abs(playerMat.GetPosition().y-mPosition.y)>=2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		randomTarget = Vector3(GetRand(ArrowAccuracy * 2) - ArrowAccuracy,
			                   GetRand(ArrowAccuracy * 2) - ArrowAccuracy,
			                   GetRand(ArrowAccuracy * 2) - ArrowAccuracy);

		//world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyGunBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(1, 1, 1), randomTarget, 2.0f));
		//world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyVaristorBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(1), randomTarget));
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<ParachuteBombBullet>(world, mPosition, Vector3(0), Vector3(1), playerMat.GetPosition().y + 5.0f));
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
	DrawCapsule3D(startPos, endPos, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

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
	//parameter.isDead = true;
}