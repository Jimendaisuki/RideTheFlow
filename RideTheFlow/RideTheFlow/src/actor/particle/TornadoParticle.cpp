#include "TornadoParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"

TornadoParticle::TornadoParticle(Vector3& position_, std::weak_ptr<Tornado> tornade_)
:
tornade(tornade_),
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
timer(0.0f),
tornadeAddPosition(Vector3::Zero),
drawFrame(Random::GetInstance().Range(0, 2))
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = Random::GetInstance().Range(10.0f, 15.0f);
	lifeParam.isDead = false;

	moveParam.pos = tornadePos;

	drawParam.drawID = MODEL_ID::CLOUD_MODEL;
	drawParam.size = 10.0f;
	drawParam.alpha = 0.9f;
}

void TornadoParticle::OnUpdate()
{
	//竜巻の動きを取得
	Vector3 pos = tornade._Get()->GetParameter().mat.GetPosition();
	tornadeMove = pos - tornadePos;
	tornadePos = pos;

	tornadeDegree += tornadeSpeed * Time::DeltaTime;
	risingSpeed += risingAddSpeed * Time::DeltaTime;
	tornadeRadius += tornadeAddRadius * Time::DeltaTime;

	//モデル回転
	rotate += Vector3(
		2.0f,
		2.0f,
		0.0f);

	//回転加える前の座標
	position += tornadeMove;
	position.y += risingSpeed * Time::DeltaTime;

	//回転加えた後の座標
	tornadeAddPosition = Vector3(
		Math::Cos(tornadeDegree) * tornadeRadius,
		0.0f,
		Math::Sin(tornadeDegree) * tornadeRadius);
	//position += tornadeAddPosition;

	mat =
		Matrix4::Scale(scale) *
		Matrix4::Translate(position + tornadeAddPosition);

	//セルフビルボード計算
	up = Vector3::Normalize(Camera::GetInstance().Up.Get());
	front = Vector3::Normalize(Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get());
	left = Vector3::Cross(up, front);
	mat.SetFront(front);
	mat.SetUp(up);
	mat.SetLeft(left);
}

void TornadoParticle::Draw() const
{
	//Model::GetInstance().Draw2DBlend(drawParam.drawID, moveParam.pos, 0, drawParam.size, drawParam.billboardOrigin, 0, drawParam.blendMode, drawParam.alpha);
	Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, drawParam.alpha, rotate, drawParam.size, true);
}