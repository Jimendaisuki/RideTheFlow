#include "CastleAddParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"
#include "../../math/Quaternion.h"
#include "../../WindAndTornadoSetting.h"

CastleAddParticle::CastleAddParticle(const Vector3& position_, float sizeBase, float sizeAddMin, float sizeAddMax)
:
xrot(Random::GetInstance().Range(-1.0f, 1.0f)),
yrot(Random::GetInstance().Range(-1.0f, 1.0f)),
rotmat(Matrix4::Identity),
mat(Matrix4::Identity),
addAlpha(Random::GetInstance().Range(-0.6f,-0.5f)),
rotationSpeed(Random::GetInstance().Range(-180.0f, 180.0f)),
addSizeSpeed(Random::GetInstance().Range(0.01f,0.03f)),
timer(0.0f)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = SmokeLifeLimit;
	lifeParam.isDead = false;

	moveParam.pos = position_;

	drawParam.drawID = MODEL_ID::CASTLE_ADD_MODEL;
	drawParam.size = sizeBase + Random::GetInstance().Range(sizeAddMin, sizeAddMax);
	drawParam.alpha = 1.0f;
}

void CastleAddParticle::OnUpdate()
{
	drawParam.size += addSizeSpeed * Time::GetInstance().deltaTime();

	drawParam.alpha = Math::Cos((lifeParam.lifeTime / lifeParam.lifeTimeLimit) * 90);

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