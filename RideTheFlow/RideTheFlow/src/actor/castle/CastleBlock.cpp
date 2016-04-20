#include "CastleBlock.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../graphic/TextDraw.h"
#include "../../math/Math.h"
#include "../../game/Random.h"

CastleBlock::CastleBlock(IWorld& world, Vector3& position_, const float& risingSpeed_) :
Actor(world),
tornadePos(Vector3::Zero),
tornadeMove(Vector3::Zero),
tornadeRadius(Random::GetInstance().Range(1,3)),
tornadeSpeed(360.0f),
risingSpeed(risingSpeed_),
risingAddSpeed(Random::GetInstance().Range(3, 29)),
scale(Vector3(1.0f)),
position(position_),
rotate(Vector3::Zero),
timer(0.0f),
tornadeAddPosition(Vector3::Zero)
{
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

	timer += Time::DeltaTime;
	if (timer > 10.0f)
		parameter.isDead = true;

	//âÒì]â¡Ç¶ÇÈëOÇÃç¿ïW
	position += tornadeMove;
	position.y += risingSpeed * Time::DeltaTime;
	rotate += Vector3(
		360.0f* Time::DeltaTime,
		360.0f* Time::DeltaTime,
		0.0f);

	//âÒì]â¡Ç¶ÇΩå„ÇÃç¿ïW
	tornadeAddPosition = Vector3(
		Math::Cos(timer * tornadeSpeed) * tornadeRadius,
		0.0f,
		Math::Sin(timer * tornadeSpeed) * tornadeRadius);
	position += tornadeAddPosition;

	risingSpeed += risingAddSpeed * Time::DeltaTime;
	tornadeRadius += Time::DeltaTime;

	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateY(rotate.y) *
		Matrix4::RotateZ(rotate.z) *
		Matrix4::RotateX(rotate.x) *
		Matrix4::Translate(position);
}
void CastleBlock::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::BOX_MODEL, parameter.mat);
}
void CastleBlock::OnCollide(Actor& other, CollisionParameter colpara)
{

}