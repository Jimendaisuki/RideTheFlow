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
//èÈÇÃè„å¿äKêî
const int Rank = 4;
//èÈÇ™êœÇ›Ç†Ç™ÇÈéûä‘(ïb)
const float RankUpSecond = 5.0f;
//èÈÇ™çUåÇÇµÇƒÇ≠ÇÈîÕàÕ
const float AttackRange = 300.0f;
//ñàïbÇÃçUåÇ(ÇPïbä‘Ç…âΩå¬ãÖÇèoÇ∑Ç©)
const float ParSecondAttack = 1.0f;

MasterCastle::MasterCastle(IWorld& world, Vector3 position, Vector3 rotate, Vector3 scale) :
Actor(world),
attackTime(0),
castleTime(0),
mRank(Rank),
mPosition(position),
startPos(Vector3::Zero),
endPos(Vector3::Zero),
playerMat(Matrix4::Identity)
{
	parameter.isDead = false;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::Translate(position);

	Vector2 side = Vector2(scale.x, scale.z) / 2;
	parameter.radius = sqrtf(side.x * side.x + side.y + side.y);

	startPos = Matrix4::GetPosition(parameter.mat);
	endPos = Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3::Up;
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
	if (castleTime >= RankUpSecond&&mRank>0)
	{
		mRank--;
		world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world, Vector3(mPosition.x, endPos.y*(Rank - mRank), mPosition.z), Vector3(0, 0, 0), Vector3(30, 30, 30), ParSecondAttack, AttackRange));
		castleTime = 0.0f;
	}

	if (attackTime >= 1.0f / ParSecondAttack)
	{
		attackTime = 0.0f;
		if (Vector3::Distance(playerMat.GetPosition(), mPosition) > AttackRange) return;
		switch (GetRand(2))
		{
		case 0:
			//ÉoÉOÇ¡ÇƒÇÈ
			/*world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(5, 5, 5), 50.0f));*/
			break;
		case 1:
			world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyGunBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(5, 5, 5), 2.0f));
			break;
		case 2:
			world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyVaristorBullet>(world, mPosition, Vector3(0, 0, 0), Vector3(5, 5, 5)));
			break;
		case 3:
			//ÉpÉâÉVÉÖÅ[ÉgÇÕÇ¢ÇÁÇ»Ç¢
			//world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<ParachuteBombBullet>(world, mPosition,100.0f));
			break;
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