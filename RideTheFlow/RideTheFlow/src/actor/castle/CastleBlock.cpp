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
tornadeRadius(2.0f),
tornadeSpeed(360.0f),
risingSpeed(risingSpeed_),
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
	timer += Time::DeltaTime;
	if (timer > 10.0f)
		parameter.isDead = true;

	//âÒì]â¡Ç¶ÇÈëOÇÃç¿ïW
	position.y += risingSpeed * Time::DeltaTime;
	rotate += Vector3(2.0f, 2.0f, 0.0f);

	//âÒì]â¡Ç¶ÇΩå„ÇÃç¿ïW
	tornadeAddPosition = Vector3(
		Math::Cos(timer * tornadeSpeed) * tornadeRadius,
		0.0f,
		Math::Sin(timer * tornadeSpeed) * tornadeRadius);
	position += tornadeAddPosition;

	risingSpeed += Time::DeltaTime;
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