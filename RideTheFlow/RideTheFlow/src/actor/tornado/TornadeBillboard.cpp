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

TornadeBillboard::TornadeBillboard(IWorld& world, Vector3& position_, std::weak_ptr<Tornado> tornade_) :
Actor(world),
tornadePos(Vector3::Zero),
tornadeMove(Vector3::Zero),
tornadeRadius(Random::GetInstance().Range(10.0f, 20.0f)),
tornadeAddRadius(Random::GetInstance().Range(20.0f, 30.0f)),
tornadeSpeed(1000.0f),
tornadeDegree(Random::GetInstance().Range(1.0f, 360.0f)),
risingSpeed(Random::GetInstance().Range(120.0f, 150.0f)),
risingAddSpeed(Random::GetInstance().Range(0, 2)),
scale(200.0f),
position(position_),
rotate(Vector3::Zero),
drawPosition(Vector2::Zero),
timer(0.0f),
tornadeAddPosition(Vector3::Zero),
drawFrame(Random::GetInstance().Range(0, 2)),
tornade(tornade_)
{
	world.EachActor(ACTOR_ID::TORNADO_ACTOR, [&](const Actor& other){
		tornadePos = other.GetParameter().mat.GetPosition();
	});

	parameter.isDead = false;
	parameter.id = ACTOR_ID::TORNADO_ACTOR;
	rotate = Vector3(Random::GetInstance().Range(0.0f, 359.0f), Random::GetInstance().Range(0.0f, 359.0f), 0.0f);
}
TornadeBillboard::~TornadeBillboard()
{

}
void TornadeBillboard::Update()
{
	Vector3 pos = tornade._Get()->GetParameter().mat.GetPosition();
	tornadeMove = pos - tornadePos;
	tornadePos = pos;

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
	Model::GetInstance().Draw2DBlend(
		MODEL_ID::SMOKE_2D, parameter.mat.GetPosition(), drawFrame, scale, BLEND_MODE::Mul, 150);
	//Sprite::GetInstance().DrawBlend(SPRITE_ID::BEGIN_SPRITE, drawPosition, Vector2(200, 0), scale, 0, BLEND_MODE::Sub);
}
void TornadeBillboard::OnCollide(Actor& other, CollisionParameter colpara)
{

}