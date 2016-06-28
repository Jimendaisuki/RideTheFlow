#include "SandParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"

SandParticle::SandParticle(const Vector3& position_, const Vector3& vec_)
:
up(Vector3::Zero),
left(Vector3::Zero),
front(Vector3::Zero),
rotmat(Matrix4::Identity)
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = 9.0f;
	lifeParam.isDead = false;

	moveParam.pos = position_;
	moveParam.vec = vec_;
	moveParam.speed = Random::GetInstance().Range(30.0f, 60.0f);

	drawParam.drawID = MODEL_ID::SAND_MODEL;
	drawParam.size = 30.0f;
	drawParam.alpha = 0.0f;
	drawParam.blendMode = BLEND_MODE::Alpha;
	drawParam.billboardOrigin = Vector2(0, 0);

	//MV1SetMaterialDrawAlphaTestAll(Model::GetInstance().GetHandle(MODEL_ID::SAND_MODEL), true, DX_CMP_GREATEREQUAL, 80);
}

void SandParticle::OnUpdate()
{
	////セルフビルボード計算
	up = Vector3::Normalize(Camera::GetInstance().Up.Get());
	front = Vector3::Normalize(Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get());
	left = Vector3::Cross(up, front);
	//up = Vector3::Up;
	//front = Vector3::Normalize(Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get());
	//left = Vector3::Left;

	drawParam.alpha = Math::Sin(180.0f * lifeParam.lifeTime / lifeParam.lifeTimeLimit);

	//最終的な計算結果
	rotmat.SetFront(front);
	rotmat.SetUp(up);
	rotmat.SetLeft(left);

	moveParam.pos += moveParam.vec * moveParam.speed *Time::DeltaTime;
}

void SandParticle::Draw() const
{
	//Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, rotmat.GetRotateDegree(), Vector3(drawParam.size));
	Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, drawParam.alpha, rotmat.GetRotateDegree(), drawParam.size, true);
}