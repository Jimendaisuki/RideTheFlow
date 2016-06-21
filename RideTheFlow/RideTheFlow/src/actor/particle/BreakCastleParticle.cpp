#include "BreakCastleParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"
#include "../../math/Quaternion.h"

BreakCastleParticle::BreakCastleParticle(const MODEL_ID& id_, const Vector3& position_, float rotX_, float rotY_)
:
rotX(rotX_),
rotY(rotY_),
rotationSpeed(Random::GetInstance().Range(-180.0f, 180.0f)),
rotmat(Matrix4::Identity),
mat(Matrix4::Identity),
rotXSpeed(0.0f),
rotYSpeed(0.0f),
rotXAdd(Random::GetInstance().Range(7.0f, 10.0f)),
rotYAdd(Random::GetInstance().Range(9.0f, 12.0f)),
risingSpeed(Random::GetInstance().Range(10.0f, 12.0f)),
tornadeRadius(0.0f),
tornadeDegree(Random::GetInstance().Range(0.0f, 360.0f)),
tornadeAddRadius(Random::GetInstance().Range(5.0f, 8.0f)),
tornadeSpeed(160.0f),
tornadeAddPosition(Vector3::Zero)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 20.0f;
	lifeParam.isDead = false;

	moveParam.pos = position_;

	drawParam.drawID = id_;
	drawParam.size = 30.0f;

}

void BreakCastleParticle::OnUpdate()
{
	if (rotXSpeed < 90.0f)
		rotXSpeed += rotXAdd * Time::DeltaTime;
	if (rotXSpeed < 190.0f)
		rotYSpeed += rotYAdd * Time::DeltaTime;
	rotX += rotXSpeed * Time::DeltaTime;
	rotY += rotYSpeed * Time::DeltaTime;
	rotmat =
		Matrix4::RotateX(rotX) *
		Matrix4::RotateY(rotY);

	//‰ñ“]•ª‚ðŒvŽZ
	tornadeAddPosition = Vector3(
		Math::Cos(tornadeDegree) * tornadeRadius,
		0.0f,
		Math::Sin(tornadeDegree) * tornadeRadius);
	if (tornadeRadius < 50.0f)
		tornadeRadius += tornadeAddRadius * Time::DeltaTime;
	tornadeDegree += tornadeSpeed * Time::DeltaTime;

	//¸‚Á‚Ä‚¢‚­
	moveParam.pos.y += risingSpeed * Time::DeltaTime;

	mat =
		Matrix4::Scale(drawParam.size) *
		rotmat *
		Matrix4::Translate(moveParam.pos + tornadeAddPosition);
}

void BreakCastleParticle::Draw() const
{
	Model::GetInstance().Draw(drawParam.drawID, mat.GetPosition(), mat.GetRotateDegree(), mat.GetScale());
}