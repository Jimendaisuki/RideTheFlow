#include "CastleTop.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include"CastleParameter.h"
#include "../NoShipArea.h"

CastleTop::CastleTop(IWorld& world, Vector3 position, MasterCastle& mc,float rotateY,float scale) :
Actor(world),
playerMat(Matrix4::Identity),
startPos(position),
endPos(position),
mPosition(position),
mScale(30.0f*scale),
castleDown(true),
castleUpTimer(0.0f)
{
	parameter.id = ACTOR_ID::CASTLE_ACTOR;

	parameter.isDead = false;
	parameter.radius = 35*scale;
	parameter.height = Vector3(0.0f, 30.0f, 0.0f)*scale;
	parameter.mat =
		Matrix4::Scale(mScale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(rotateY) *
		Matrix4::Translate(position);
	mMc = &mc;
	mRank = 0.0f;
	world.Add(ACTOR_ID::NO_SHIP_AREA_ACTOR, std::make_shared<NoShipArea>(world,
		parameter.mat.GetPosition() + Vector3(0.0f, parameter.radius*4, 0.0f)
		, parameter.radius, *this));
	mRotateY = rotateY;
	sevePos = mPosition;
	mScaleFloat = scale;
	seveRank = mc.getRank();
	mRank = seveRank;
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

	castleUpTimer += 5.0f*Time::GetInstance().deltaTime();
	if (seveRank != mRank)
	{
		startPos = parameter.mat.GetPosition();
		endPos = (mMc->GetParameter().mat.GetPosition() + mMc->GetParameter().height) +
			(Vector3(0.0f,34.0f,0.0f)*2.4f)*mRank;
		castleUpTimer = 0.0f;
	}

	mPosition = Vector3::Lerp(startPos, endPos, castleUpTimer);
	//マスターが壊れたら自分も壊れる
	if (mMc->GetParameter().isDead)
	{
		parameter.isDead = true;
		world.Add(ACTOR_ID::CASTLE_BREAK_ACTOR, std::make_shared<BreakCastle>(world, mPosition, CASTLE_SELECT::CHILD_CASTLE, mMc->getBreakSelect()));
	}
	parameter.mat = Matrix4::Scale(mScale)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::Translate(mPosition);
	seveRank = mRank;
}

void CastleTop::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP2_MODEL, parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::CASTLE_TOP_MODEL, parameter.mat*Matrix4::Translate(Vector3(0, 40, 0)*mScaleFloat));
}

void CastleTop::OnCollide(Actor& other, CollisionParameter colpara)
{

}