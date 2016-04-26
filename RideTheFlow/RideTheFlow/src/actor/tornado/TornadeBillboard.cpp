#include "TornadeBillboard.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../graphic/TextDraw.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../graphic/Sprite.h"

TornadeBillboard::TornadeBillboard(IWorld& world, Vector3& position_) :
Actor(world),
tornadePos(Vector3::Zero),
tornadeMove(Vector3::Zero),
tornadeRadius(Random::GetInstance().Range(10.0f, 15.0f)),
tornadeAddRadius(Random::GetInstance().Range(10.0f, 15.0f)),
tornadeSpeed(360.0f),
tornadeDegree(Random::GetInstance().Range(1.0f, 360.0f)),
risingSpeed(Random::GetInstance().Range(50.0f, 60.0f)),
risingAddSpeed(Random::GetInstance().Range(15, 20)),
scale(100.0f),
position(position_),
rotate(Vector3::Zero),
drawPosition(Vector2::Zero),
timer(0.0f),
tornadeAddPosition(Vector3::Zero)
{
	world.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		tornadePos = other.GetParameter().mat.GetPosition();
	});

	parameter.isDead = false;
	parameter.id = ACTOR_ID::CASTLE_ACTOR;
	rotate = Vector3(Random::GetInstance().Range(0.0f, 359.0f), Random::GetInstance().Range(0.0f, 359.0f), 0.0f);
}
TornadeBillboard::~TornadeBillboard()
{

}
void TornadeBillboard::Update()
{
	world.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		Vector3 pos = other.GetParameter().mat.GetPosition();
		tornadeMove = pos - tornadePos;
		tornadePos = pos;
	});

	timer += Time::DeltaTime;
	if (timer > 10.0f)
		parameter.isDead = true;
	tornadeDegree += tornadeSpeed * Time::DeltaTime;
	risingSpeed += risingAddSpeed * Time::DeltaTime;
	tornadeRadius += tornadeAddRadius * Time::DeltaTime;

	//ÉÇÉfÉãâÒì]
	rotate += Vector3(
		2.0f,
		2.0f,
		0.0f);

	//âÒì]â¡Ç¶ÇÈëOÇÃç¿ïW
	position += tornadeMove;
	position.y += risingSpeed * Time::DeltaTime;

	//âÒì]â¡Ç¶ÇΩå„ÇÃç¿ïW
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

	drawPosition = ConvWorldPosToScreenPos(parameter.mat.GetPosition().ToVECTOR());
}
void TornadeBillboard::Draw() const
{
	Model::GetInstance().Draw2DBlend(MODEL_ID::SMOKE_MODEL2D, parameter.mat.GetPosition(), 0, scale, BLEND_MODE::Sub,128);
	//Sprite::GetInstance().DrawBlend(SPRITE_ID::BEGIN_SPRITE, drawPosition, Vector2(200, 0), scale, 0, BLEND_MODE::Sub);
}
void TornadeBillboard::OnCollide(Actor& other, CollisionParameter colpara)
{

}