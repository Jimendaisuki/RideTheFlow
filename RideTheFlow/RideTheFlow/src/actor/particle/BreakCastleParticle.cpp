#include "BreakCastleParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"
#include "../../math/Quaternion.h"

BreakCastleParticle::BreakCastleParticle(const MODEL_ID& id_, const BREAK_SELECT& break_, Vector3* parentPosition_, const Vector3& position_, const Vector3& vec_, float rotX_, float rotY_)
:
breakSelect(break_),
pParentPosition(parentPosition_),
rotX(rotX_),
rotY(rotY_),
rotmat(Matrix4::Identity),
mat(Matrix4::Identity),
rotXSpeed(0.0f),
rotYSpeed(0.0f),
rotXAdd(0.0f),
rotYAdd(0.0f),
risingSpeed(0.0f),
tornadeRadius(0.0f),
tornadeDegree(0.0f),
tornadeAddRadius(0.0f),
tornadeSpeed(160.0f),
tornadeAddPosition(Vector3::Zero),

flowRisingSpeed	(0.0f),
flowRotXSpeed	(0.0f),
flowRotYSpeed	(0.0f),
flowRotXAdd		(0.0f),
flowRotYAdd		(0.0f),
flowAddPosition(Vector3::Zero)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 12.0f;
	lifeParam.isDead = false;

	moveParam.pos = position_;
	moveParam.vec = vec_;

	drawParam.drawID = id_;
	drawParam.alpha = 0.2f;
	drawParam.size = 30.0f;
	if (breakSelect == BREAK_SELECT::TORNADO)
	{
		rotXAdd			 = Random::GetInstance().Range(14.0f, 20.0f);
		rotYAdd			 = Random::GetInstance().Range(18.0f, 24.0f);
		risingSpeed		 = Random::GetInstance().Range(30.0f, 40.0f);
		tornadeDegree	 = Random::GetInstance().Range(0.0f, 360.0f);
		tornadeAddRadius = Random::GetInstance().Range(10.0f, 16.0f);
	}
	else if(breakSelect == BREAK_SELECT::WIND_FLOW)
	{
		flowRisingSpeed	= Random::GetInstance().Range(3.0f, 8.0f)	;
		flowRotXSpeed	= Random::GetInstance().Range(-10.0f, 10.0f);
		flowRotYSpeed	= Random::GetInstance().Range(-10.0f, 10.0f);
		flowRotXAdd		= Random::GetInstance().Range(-5.0f, 5.0f)	;
		flowRotYAdd		= Random::GetInstance().Range(-5.0f, 5.0f)	;
	}
	else if(breakSelect == BREAK_SELECT::WIND_BALL)
	{
		lifeParam.lifeTimeLimit = 3.0f;
		ballRotXSpeed = Random::GetInstance().Range(-90.0f, 90.0f);
		ballRotYSpeed = Random::GetInstance().Range(-90.0f, 90.0f);
		moveParam.vec.y = Random::GetInstance().Range(-30.0f, -8.0f);
	}
	
}

void BreakCastleParticle::OnUpdate()
{
	//ƒAƒ‹ƒtƒ@’l‚ÌŒvŽZ‚Í‹¤’Ê
	drawParam.alpha = (lifeParam.lifeTimeLimit - lifeParam.lifeTime) / 2.0f;

	switch (breakSelect)
	{
	case TORNADO: TornadoBreak(); break;
	case WIND_FLOW: WindFlowBreak(); break;
	case WIND_BALL: WindBallBreak(); break;
	default:
		break;
	}
}

void BreakCastleParticle::Draw() const
{
	Model::GetInstance().Draw(drawParam.drawID, mat.GetPosition(), drawParam.alpha,mat.GetRotateDegree(), mat.GetScale());
}

void BreakCastleParticle::TornadoBreak()
{
	//‰ñ“]ŒvŽZ
	if (rotXSpeed < 90.0f)
		rotXSpeed += rotXAdd * Time::DeltaTime;
	if (rotXSpeed < 190.0f)
		rotYSpeed += rotYAdd * Time::DeltaTime;
	rotX += rotXSpeed * Time::DeltaTime;
	rotY += rotYSpeed * Time::DeltaTime;

	rotmat =
		Matrix4::RotateY(rotY) *
		Matrix4::RotateX(rotX);

	//‰ñ“]•ª‚ðŒvŽZ
	tornadeAddPosition = Vector3(
		Math::Cos(tornadeDegree) * tornadeRadius,
		0.0f,
		Math::Sin(tornadeDegree) * tornadeRadius);
	if (tornadeRadius < 120.0f)
		tornadeRadius += tornadeAddRadius * Time::DeltaTime;
	tornadeDegree += tornadeSpeed * Time::DeltaTime;

	//¸‚Á‚Ä‚¢‚­
	moveParam.pos.y += risingSpeed * Time::DeltaTime;

	mat =
		Matrix4::Scale(drawParam.size) *
		rotmat *
		Matrix4::Translate(*pParentPosition + moveParam.pos + tornadeAddPosition);
}

void BreakCastleParticle::WindFlowBreak()
{
	//ˆÚ“®
	moveParam.vec.y += flowRisingSpeed * Time::DeltaTime;
	moveParam.pos += moveParam.vec * Time::DeltaTime;

	//‰ñ“]ŒvŽZ
	flowRotXSpeed += flowRotXAdd * Time::DeltaTime;
	flowRotYSpeed += flowRotYAdd * Time::DeltaTime;
	rotX += flowRotXSpeed * Time::DeltaTime;
	rotY += flowRotYSpeed * Time::DeltaTime;

	rotmat =
		Matrix4::RotateY(rotY) *
		Matrix4::RotateX(rotX);

	mat =
		Matrix4::Scale(drawParam.size) *
		rotmat *
		Matrix4::Translate(*pParentPosition + moveParam.pos);
}

void BreakCastleParticle::WindBallBreak()
{
	//ˆÚ“®
	moveParam.pos += moveParam.vec * Time::DeltaTime;

	//‰ñ“]ŒvŽZ
	rotX += ballRotXSpeed * Time::DeltaTime;
	rotY += ballRotYSpeed * Time::DeltaTime;

	rotmat =
		Matrix4::RotateY(rotY) *
		Matrix4::RotateX(rotX);

	mat =
		Matrix4::Scale(drawParam.size) *
		rotmat *
		Matrix4::Translate(*pParentPosition + moveParam.pos);
}