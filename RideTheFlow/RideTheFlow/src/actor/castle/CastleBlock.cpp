#include "CastleBlock.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../graphic/TextDraw.h"
#include "../../math/Math.h"
#include "../../game/Random.h"

static const float MODEL_SCALE = 16.0f;

CastleBlock::CastleBlock(IWorld& world, Vector3& position_) :
Actor(world),
tornadePos(Vector3::Zero),
tornadeMove(Vector3::Zero),
tornadeRadius(Random::GetInstance().Range(60.0f, 80.0f)),
tornadeAddRadius(Random::GetInstance().Range(8.0f, 15.0f)),
tornadeSpeed(360.0f),
tornadeDegree(Random::GetInstance().Range(1.0f, 360.0f)),
risingSpeed(Random::GetInstance().Range(8.0f, 10.0f)),
risingAddSpeed(Random::GetInstance().Range(5, 20)),
scale(Vector3(1.0f)),
position(position_),
rotate(Vector3::Zero),
timer(0.0f),
tornadeAddPosition(Vector3::Zero)
{
	scale = Vector3(10.0f / risingAddSpeed) * MODEL_SCALE;
	world.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		tornadePos = other.GetParameter().mat.GetPosition();
	});

	parameter.isDead = false;
	parameter.id = ACTOR_ID::CASTLE_ACTOR;
	rotate = Vector3(Random::GetInstance().Range(0.0f, 359.0f), Random::GetInstance().Range(0.0f, 359.0f), 0.0f);
}
CastleBlock::~CastleBlock()
{

}
void CastleBlock::Update()
{
	world.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		Vector3 pos = other.GetParameter().mat.GetPosition();
		tornadeMove = pos - tornadePos;
		tornadePos = pos;
	});

	timer += Time::GetInstance().deltaTime();
	if (timer > 10.0f)
		parameter.isDead = true;
	tornadeDegree += tornadeSpeed * Time::GetInstance().deltaTime();
	risingSpeed += risingAddSpeed * Time::GetInstance().deltaTime();
	tornadeRadius += tornadeAddRadius * Time::GetInstance().deltaTime();

	////ƒ‚ƒfƒ‹‰ñ“]
	//rotate += Vector3(
	//	2.0f,
	//	2.0f,
	//	0.0f);

	//‰ñ“]‰Á‚¦‚é‘O‚ÌÀ•W
	position += tornadeMove;
	position.y += risingSpeed * Time::GetInstance().deltaTime();

	//‰ñ“]‰Á‚¦‚½Œã‚ÌÀ•W
	tornadeAddPosition = Vector3(
		Math::Cos(tornadeDegree) * tornadeRadius,
		0.0f,
		Math::Sin(tornadeDegree) * tornadeRadius);
	//position += tornadeAddPosition;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::Translate(position + tornadeAddPosition);
}
void CastleBlock::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::BOX_MODEL, parameter.mat);
}
void CastleBlock::OnCollide(Actor& other, CollisionParameter colpara)
{
	parameter.isDead = true;
}