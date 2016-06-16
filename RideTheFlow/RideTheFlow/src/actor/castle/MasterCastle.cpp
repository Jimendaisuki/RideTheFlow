#include "MasterCastle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../enemy/EnemyBullet.h"
#include "castle.h"
#include "../../game/Random.h"
#include "CastleParameter.h"
#include "CastleTop.h"
#include "../particle/CastleAdd.h"
#include "CastleBlock.h"
#include "../enemy/ArmyEnemy.h"
#include "../enemy/ShipEnemy.h"
MasterCastle::MasterCastle(IWorld& world, Vector3 position,bool spawnShip) :
Actor(world),
attackTime(0),
castleTime(0),
attackRag(0),
arrowCount(0),
mRank(Rank),
mPosition(position),
playerMat(Matrix4::Identity),
rankUp(false),
rankUpRag(false),
rankUpRagTimer(0),
mScale(45, 45, 45),
spawanArmyTimer(0.0f),
spawnShipTimer(0.0f),
mSpawnShip(spawnShip),
InvincibleTimer(0.0f)
{
    parameter.radius = 35;
	parameter.HP = MasterCastleHp;
	parameter.isDead = false;
	parameter.height = Vector3(0.0f, 70.0f, 0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<CastleTop>(world,parameter.mat.GetPosition()+Vector3(0,100,0),*this));
}

MasterCastle::~MasterCastle()
{
	
}

void MasterCastle::Update()
{
	//�e����
	castleTime += Time::DeltaTime;
	//�����蔻��
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::STAGE_ACTOR, COL_ID::ARMYENEMY_STAGE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::TORNADO_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::WIND_ACTOR, COL_ID::CASTLE_WIND_COL);
	//�ςݏd�Ȃ��
	if (castleTime >= RankUpSecond&&mRank>0)
	{
		mRank--;
		rankUp = true;
		castleTime = 0.0f;
		rankUpRag = true;

		//��o�����̃p�[�e�B�N���𐶐�
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleAdd>(world, mPosition + Vector3(0.0f, parameter.radius * 2, 0.0f) + Vector3(0.0f, 20.0f*(Rank - mRank), 0.0f) + Vector3(0, 10 * (Rank - mRank), 0)));

	}
	else
	{
		rankUp = false;
	}
	//�邪1�b��ɏo��
	if (rankUpRag)
	{
		rankUpRagTimer += Time::DeltaTime;
		if (rankUpRagTimer >= 1.0f)
		{
			world.Add(ACTOR_ID::CASTLE_ACTOR, std::make_shared<Castle>(world,
				mPosition + Vector3(0.0f, parameter.radius * 2, 0.0f) + Vector3(0.0f, 20.0f*(Rank - mRank), 0.0f) + Vector3(0, 10 * (Rank - mRank), 0)
				, *this));
			rankUpRagTimer = 0.0f;
			rankUpRag = false;
		}
	}
	//�X�e�[�W�ɓ���������~�܂�
 	if (downCastle)
	{
		mPosition.y -= 50.0f*Time::DeltaTime;
	}
	downCastle = true;


	if (mSpawnShip)
	{
		spawnShipTimer += Time::DeltaTime;
		if (spawnShipTimer >= SpawnShipEnemyTime&&world.GetActorCount(ACTOR_ID::ENEMY_ACTOR, ACTOR_ID::SHIP_ENEMY_ACTOR)<SpawnMaxShipEnemey)
		{
			world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ShipEnemy>(world, parameter.mat.GetFront()*-3+parameter.mat.GetUp()*5 + mPosition));
			spawnShipTimer = 0.0f;
		}
	}
	else
	{
		spawanArmyTimer += Time::DeltaTime;
		if (spawanArmyTimer >= SpawnArmyEnemyTime&&world.GetActorCount(ACTOR_ID::ENEMY_ACTOR, ACTOR_ID::ARMY_ENEMY_ACTOR)<SpawnMaxArmyEnemy)
		{
			world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<ArmyEnemy>(world, parameter.mat.GetFront()*-2 +Vector3(0,2,0)+ mPosition));
			spawanArmyTimer = 0.0f;
		}
	}

	//���G����
	if (!damage)
	{
		InvincibleTimer += Time::DeltaTime;
		if (CastleInvincibleTime <= InvincibleTimer)
		{
			InvincibleTimer = 0.0f;
			damage = true;
		}
	}
	//hp��0�ɂȂ����玀��
	if (parameter.HP <= 0)
	{
		//���ꂫ���΂�
		for (int i = 0; i < 8; i++){
			world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<CastleBlock>(world, mPosition + Vector3(0.0f, Random::GetInstance().Range(-10.0f, 10.0f), 0.0f)));
		}
		parameter.isDead = true;
	}


	//�}�g���b�N�X�v�Z
	parameter.mat =
		Matrix4::Scale(mScale)*
		Matrix4::Translate(mPosition);
}

void MasterCastle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MASTER_MODEL, parameter.mat);
	//DrawFormatString(0, 500, GetColor(0, 0, 0), "�G�̐�   %d", world.GetActorCount(ACTOR_ID::ENEMY_ACTOR,ACTOR_ID::ARMY_ENEMY_ACTOR));
}

void MasterCastle::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL&&damage)
	{
		parameter.HP -= CastleDamegeTornado;
		damage = false;
	}
	if (colpara.colID == COL_ID::CASTLE_WIND_COL&&damage)
	{
		parameter.HP -= CastleDamegeWind;
		damage = false;
	}

	if (colpara.colID == COL_ID::ARMYENEMY_STAGE_COL)
	{
		downCastle = false;
	}
}