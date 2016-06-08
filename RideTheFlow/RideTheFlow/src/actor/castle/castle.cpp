#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "CastleCannon.h"
#include "CastleDoragonSpear.h"

#include"CastleParameter.h"

Castle::Castle(IWorld& world, Vector3 position,Actor& _parent) :
Actor(world),
arrowCount(0),
attackRag(0.0f),
playerMat(Matrix4::Identity),
mPosition(position),
mScale(30,30,30),
mAttackTime(0.0f),
castleDown(true),
isLook(false)
{
	parameter.isDead = false;
	parameter.radius = 17;
	parameter.height = Vector3(0.0f,34.0f,0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	parent =&_parent;
	//��ɏ���Ă���G�̈ʒu���Z�b�g
	CastleEnemyPosSet();
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon01, *this, -90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon02, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon03, *this, 90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleCannon>(world, castleEnemyPos.cannon04, *this, 180));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear01, *this, -90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear02, *this, 0));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear03, *this, 90));
	world.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<CastleDoragonSpear>(world, castleEnemyPos.Spear04, *this, 180));
}


Castle::~Castle()
{

}

void Castle::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	//�����蔻��
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CASTLE_ACTOR, COL_ID::CASTLE_CASTLE_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);
	//��ɓ���������X�g�b�v
	if (castleDown)
	{
		velocity.y -= 400.0f*Time::DeltaTime;
		if (velocity.y <= -400.0f)
			velocity.y = -400.0f;
	}
	else
	{
		velocity = 0;
	}
	castleDown = true;
	mPosition += velocity*Time::DeltaTime;

	//�}�X�^�[����ꂽ�玩��������
	if (parent->GetParameter().isDead)
	{
		parameter.isDead = true;
	}

	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::Translate(mPosition);
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_BASE_MODEL, parameter.mat);
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{

	//�S�������ĂȂ�������
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
	{
		//�����Ƀ_���[�W
	}
	if (colpara.colID == COL_ID::CASTLE_CASTLE_COL&&colpara.colFlag)
	{
		castleDown = false;
	}
}
void Castle::CastleEnemyPosSet()
{
	castleEnemyPos.cannon01 = 
		parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon02 =
		parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*-32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon03 =
		parameter.mat.GetFront().Normalized()*25.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.cannon04 =
		parameter.mat.GetFront().Normalized()*-25.0f +
		parameter.mat.GetLeft().Normalized()*32.0f +
		parameter.mat.GetUp().Normalized()*5.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear01 =
		parameter.mat.GetFront().Normalized()*22.0f +
		parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear02 =
		parameter.mat.GetFront().Normalized()*0.0f +
		parameter.mat.GetLeft().Normalized()*22.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear03 =
		parameter.mat.GetFront().Normalized()*-22.0f +
		parameter.mat.GetLeft().Normalized()*0.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();

	castleEnemyPos.Spear04 =
		parameter.mat.GetFront().Normalized()*0.0f +
		parameter.mat.GetLeft().Normalized()*-22.0f +
		parameter.mat.GetUp().Normalized()*15.0f +
		parameter.mat.GetPosition();
}