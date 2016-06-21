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
addSizeSpeed(Random::GetInstance().Range(0.01f,0.03f)),
timer(0.0f)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 2.0f;
	lifeParam.isDead = false;

	moveParam.pos = position_;

	drawParam.drawID = MODEL_ID::CASTLE_ADD_MODEL;
	drawParam.size = 0.03f + Random::GetInstance().Range(-0.03f, 0.01f);
	drawParam.alpha = 1.2f;
}

void CastleAddParticle::OnUpdate()
{
	drawParam.size += addSizeSpeed * Time::DeltaTime;

	drawParam.alpha += addAlpha * Time::DeltaTime;

	mat = 
		Matrix4::Scale(drawParam.size) *
		Matrix4::Translate(moveParam.pos);
}

void CastleAddParticle::Draw() const
{
	Model::GetInstance().Draw(drawParam.drawID, mat.GetPosition(), drawParam.alpha, mat.GetRotateDegree(), mat.GetScale() - 0.03f);
	Model::GetInstance().Draw(drawParam.drawID, mat.GetPosition(), drawParam.alpha, mat.GetRotateDegree(), mat.GetScale() - 0.02f);
	Model::GetInstance().Draw(drawParam.drawID, mat.GetPosition(), drawParam.alpha, mat.GetRotateDegree(), mat.GetScale());
}