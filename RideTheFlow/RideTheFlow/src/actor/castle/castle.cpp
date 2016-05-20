#include "castle.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"

#include "../EnemyBullet.h"

#include"CastleParameter.h"

Castle::Castle(IWorld& world, Vector3 position) :
Actor(world),
arrowCount(0),
attackRag(0.0f),
playerMat(Matrix4::Identity),
mPosition(position),
mScale(30,30,30)
{
	//MV1_REF_POLYGONLIST castleModel= MV1GetReferenceMesh(Model::GetInstance().GetHandle(MODEL_ID::CASTLE_MODEL), -1, FALSE);

	//float castleMin = sqrtf(castleModel.MinPosition.x * castleModel.MinPosition.x + castleModel.MinPosition.z * castleModel.MinPosition.z);;
	//float castleMax = sqrtf(castleModel.MaxPosition.x * castleModel.MaxPosition.x + castleModel.MaxPosition.z * castleModel.MaxPosition.z);;
	//parameter.radius=Math::Max(castleMin, castleMax);
	//parameter.height = castleModel.MaxPosition.y-castleModel.MinPosition.y;
	Vector2 side = Vector2(mScale.x, mScale.z) / 2;
	parameter.isDead = false;
	parameter.radius = sqrtf(side.x * side.x + side.y + side.y);
	parameter.height = Vector3(0.0f,30.0f,0.0f);
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	mSecondAttack = SecondAttack;
	mArrowNumber = ArrowNumber;
	mAttackTime = 0.0f;
	isLook = false;
}

Castle::~Castle()
{

}

void Castle::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::CLOUD_ACTOR, COL_ID::PLAYERTOCASTLELINE_CLOUD_COL);

	//プレイヤーが見えているかどうか
	if (isLook)
	{
		mArrowNumber = ArrowNumber;
		mSecondAttack = SecondAttack;
	}
	else
	{
		mArrowNumber = NotLookArrow;
		mSecondAttack = NotLookSecondAttack;
	}
	isLook = true;

	attackRag += Time::DeltaTime;
	mAttackTime += Time::DeltaTime;

	if (mAttackTime >= mSecondAttack&&attackRag >= 0.03f&&arrowCount < mArrowNumber&&
		Vector3::Distance(playerMat.GetPosition(), mPosition) <= AttackRange&&
		abs(playerMat.GetPosition().y - mPosition.y) >= 2.0f)
	{
		attackRag = 0.0f;
		arrowCount++;
		world.Add(ACTOR_ID::ENEMY_BULLET, std::make_shared<EnemyBullet>(world, mPosition, playerMat.GetPosition()));
		if (arrowCount >= ArrowNumber)
		{
			arrowCount = 0;
			mAttackTime = 0.0f;
		}
	}
}

void Castle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_MODEL, parameter.mat);
}

void Castle::OnCollide(Actor& other, CollisionParameter colpara)
{

	//全部見えてなかったら
	if (colpara.colID == COL_ID::PLAYERTOCASTLELINE_CLOUD_COL&&colpara.colAll)
	{
		isLook = false;
	}
	if (colpara.colID == COL_ID::TORNADO_CASTLE_COL)
	{
		parameter.isDead = true;
	}
}