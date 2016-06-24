#include "CastleTop.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include"CastleParameter.h"
#include "../NoShipArea.h"

CastleTop::CastleTop(IWorld& world, Vector3 position, MasterCastle& mc,float rotateY) :
Actor(world),
playerMat(Matrix4::Identity),
mPosition(position),
mScale(30, 30, 30),
castleDown(true),
noColTimer(0),
noCol(false)
{
	parameter.id = ACTOR_ID::CASTLE_ACTOR;
	Vector2 side = Vector2(mScale.x, mScale.z) / 2;
	parameter.isDead = false;
	parameter.radius = 35;
	parameter.height = Vector3(0.0f, 30.0f, 0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	mMc = &mc;
	mRank = 0.0f;
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*4, 0.0f)
		, parameter.radius, *this));
	mRotateY = rotateY;
}

CastleTop::~CastleTop()
{

}

void CastleTop::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});

	mRank = mMc->getRank();
	float masterHeight = mMc->GetParameter().mat.GetPosition().y + mMc->GetParameter().radius * 2;
	float castleHeight = parameter.radius;

	if (!noCol)
	{
		if (masterHeight + castleHeight*(mRank) >= parameter.mat.GetPosition().y)
		{
			velocity = 0.0f;
		}
		else
		{
			velocity.y -= 400.0f*Time::DeltaTime;
		}
	}
	else
	{
		velocity.y -= 400.0f*Time::DeltaTime;
	}
	if (mMc->castleRankUp())
	{
		//�邪�o������O�ɃW�����v
		velocity.y = 400.0f;
		noCol = true;
	}
	//�W�����v����u�Ԃ͂����蔻�薳��
	if (noCol)
	{
		noColTimer += Time::DeltaTime;
		if (noColTimer >= 0.5f)
		{
			noCol = false;
			noColTimer = 0.0f;
		}
	}
	castleDown = true;
	mPosition += velocity*Time::DeltaTime;
	//�}�X�^�[����ꂽ�玩��������
	if (mMc->GetParameter().isDead)
	{
		parameter.isDead = true;
	}
	parameter.mat = Matrix4::Scale(mScale)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
}

void CastleTop::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP2_MODEL, parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP_MODEL, parameter.mat*Matrix4::Translate(Vector3(0, 40, 0)));
	DrawFormatString(0, 432, GetColor(0, 0, 0), "Rank  %d", mRank);
}

void CastleTop::OnCollide(Actor& other, CollisionParameter colpara)
{

}