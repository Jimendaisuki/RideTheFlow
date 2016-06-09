#include "CastleAddParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"
#include "../../math/Quaternion.h"

CastleAddParticle::CastleAddParticle(const Vector3& position_)
:
xrot(Random::GetInstance().Range(-1.0f, 1.0f)),
yrot(Random::GetInstance().Range(-1.0f, 1.0f)),
rotmat(Matrix4::Identity),
mat(Matrix4::Identity),
addAlpha(Random::GetInstance().Range(-0.5f,-0.4f)),
rotationSpeed(Random::GetInstance().Range(-180.0f, 180.0f)),
addSizeSpeed(Random::GetInstance().Range(0.02f,0.04f)),
timer(0.0f)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 5.0f;
	lifeParam.isDead = false;

	moveParam.pos = position_;

	drawParam.drawID = MODEL_ID::CASTLE_ADD_MODEL;
	drawParam.size = 0.09f + Random::GetInstance().Range(-0.05f, 0.02f);
	drawParam.alpha = 0.9f;
}

void CastleAddParticle::OnUpdate()
{
	drawParam.size += addSizeSpeed * Time::DeltaTime;

	if (lifeParam.lifeTime >= 1.5f)
		drawParam.alpha += addAlpha * Time::DeltaTime;

	xrot += rotationSpeed * Time::DeltaTime;
	yrot += rotationSpeed * Time::DeltaTime;
	rotmat =
		Matrix4::RotateX(xrot) *
		Matrix4::RotateY(yrot);

	mat = 
		Matrix4::Scale(drawParam.size) *
		rotmat *
		Matrix4::Translate(moveParam.pos);
}

void CastleAddParticle::Draw() const
{
	Model::GetInstance().Draw(drawParam.drawID, mat, drawParam.alpha);
}